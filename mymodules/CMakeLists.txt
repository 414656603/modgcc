set(SRC_ROOT "${CMAKE_SOURCE_DIR}")
set(GXX "${CMAKE_CXX_COMPILER}")

# 说明：本工程使用 GCC 的 C++20 Modules TS（-fmodules-ts）并通过 -fmodule-mapper=module-map
# 显式指定“模块名 -> CMI(.gcm) 文件路径”的映射。
# 由于 CMake 目前对 GCC Modules 的原生支持有限，这里用自定义命令手动：
# - 编译每个 .cppm 生成 .o + gcm.cache/<module>.gcm
# - 把生成产物/依赖导出给上层（examples/main_exe）做链接与编译顺序约束

set(MODGCC_MODULE_OBJS "")
set(MODGCC_MODULE_CMIS "")
set(MODGCC_MODULE_TARGETS "")

macro(modgcc_add_module module_name module_src)
	# module_name 必须与源码里的 `export module <name>;` 完全一致；
	# 且需要在仓库根的 module-map.in 里添加同名映射（否则 import 时找不到 CMI）。
	set(_cmi "${CMAKE_BINARY_DIR}/gcm.cache/${module_name}.gcm")
	set(_obj "${CMAKE_CURRENT_BINARY_DIR}/${module_name}.o")

	add_custom_command(
		OUTPUT "${_obj}" "${_cmi}"
		COMMAND "${CMAKE_COMMAND}" -E make_directory "${CMAKE_BINARY_DIR}/gcm.cache"
		COMMAND "${GXX}"
			${MODGCC_COMMON_COMPILE_FLAGS}
			${MODGCC_WARNING_FLAGS}
			-c "${module_src}"
			-o "${_obj}"
		DEPENDS "${MODGCC_MODULE_MAP_FILE}" "${module_src}"
		WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
		COMMAND_EXPAND_LISTS
		VERBATIM
	)

	set(_tgt "${module_name}_module")
	add_custom_target(${_tgt} DEPENDS "${_obj}" "${_cmi}")
	# 如果启用了 std header-units 的预编译（可选），模块也需要等 std CMI 就绪。
	if(MODGCC_STD_DEPS)
		add_dependencies(${_tgt} ${MODGCC_STD_DEPS})
	endif()

	list(APPEND MODGCC_MODULE_OBJS "${_obj}")
	list(APPEND MODGCC_MODULE_CMIS "${_cmi}")
	list(APPEND MODGCC_MODULE_TARGETS "${_tgt}")
endmacro()

# 在此列出你希望参与构建的模块（通常也是你在 main.cpp 或其它模块里会 import 的模块）。
# 新增模块步骤：
# 1) 新建 mymodules/<xxx>.cppm，首行写 `export module xxx;`
# 2) 在 module-map.in 增加一行：`xxx @CMAKE_SOURCE_DIR@/gcm.cache/xxx.gcm`
# 3) 在此处增加：modgcc_add_module(xxx "${SRC_ROOT}/mymodules/xxx.cppm")
modgcc_add_module(employee "${SRC_ROOT}/mymodules/employee.cppm")
modgcc_add_module(airline_ticket "${SRC_ROOT}/mymodules/airline_ticket.cppm")

# 导出给父级（根 CMakeLists.txt），examples/ 会用这些变量：
# - MODGCC_MODULE_OBJS：需要链接进可执行文件的模块对象文件
# - MODGCC_MODULE_CMIS：main.cpp 编译前必须已生成的 CMI 列表（避免 Ninja 并行导致 import 失败）
# - MODGCC_MODULE_TARGETS：对应的自定义 target，用于 add_dependencies
set(MODGCC_MODULE_OBJS "${MODGCC_MODULE_OBJS}" PARENT_SCOPE)
set(MODGCC_MODULE_CMIS "${MODGCC_MODULE_CMIS}" PARENT_SCOPE)
set(MODGCC_MODULE_TARGETS "${MODGCC_MODULE_TARGETS}" PARENT_SCOPE)

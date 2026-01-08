
set(EXAMPLE_MAIN_SRC "${CMAKE_CURRENT_LIST_DIR}/main.cpp")

# 注意：GCC 的 modules-ts 在生成 Makefile 风格 depfile（-MD/-MF）时，
# 对模块实现单元（含 `module xxx;`）可能写出 Ninja 无法解析的内容（例如 CXX_IMPORTS += ...）。
# 这会导致“编译成功但 Ninja 仍报错”的现象。
# 规避方式：对该实现单元改用自定义命令编译（不使用 -MD），并把生成的 .o 当作生成文件链接进 main_exe。
function(modgcc_target_add_module_impl_unit target unit_name unit_src)
	set(_obj "${CMAKE_CURRENT_BINARY_DIR}/${unit_name}.o")
	add_custom_command(
		OUTPUT "${_obj}"
		COMMAND "${CMAKE_CXX_COMPILER}"
			${MODGCC_COMMON_COMPILE_FLAGS}
			${MODGCC_WARNING_FLAGS}
			-c "${unit_src}"
			-o "${_obj}"
		DEPENDS
			"${unit_src}"
			"${MODGCC_MODULE_MAP_FILE}"
			${MODGCC_MODULE_CMIS}
		WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
		COMMAND_EXPAND_LISTS
		VERBATIM
	)

	set_source_files_properties("${_obj}" PROPERTIES GENERATED TRUE)
	set(_tgt "${unit_name}_unit")
	add_custom_target(${_tgt} DEPENDS "${_obj}")
	# 让实现单元确保在所有模块（尤其对应接口）CMI 生成之后再编译。
	add_dependencies(${_tgt} ${MODGCC_MODULE_TARGETS})

	# 直接把生成的 .o 挂到目标上：这样新增一个实现单元只需要调用这一行。
	target_sources(${target} PRIVATE "${_obj}")
	add_dependencies(${target} ${_tgt})
endfunction()

add_executable(main_exe
	${EXAMPLE_MAIN_SRC}
	"${CMAKE_SOURCE_DIR}/src/console_utf8.cpp"
	# 由 mymodules/ 导出的模块对象文件列表（每个 .cppm 会生成一个 .o）。
	${MODGCC_MODULE_OBJS}
)
foreach(_obj IN LISTS MODGCC_MODULE_OBJS)
	set_source_files_properties("${_obj}" PROPERTIES GENERATED TRUE)
endforeach()

# 模块 airline_ticket 的实现单元（接口/实现分离）。
modgcc_target_add_module_impl_unit(
	main_exe
	airline_ticket_impl
	"${CMAKE_SOURCE_DIR}/src/myclasssrc/airline_ticket.cpp"
)

set_target_properties(main_exe PROPERTIES CXX_SCAN_FOR_MODULES OFF)

target_compile_options(main_exe PRIVATE
	${MODGCC_COMMON_COMPILE_FLAGS}
	${MODGCC_WARNING_FLAGS}
)

# 公共头来自 demo 库（include/），console_utf8.h 仍在 src/ 内部目录。
target_include_directories(main_exe PRIVATE
	"${CMAKE_SOURCE_DIR}/src"
)

target_link_libraries(main_exe PRIVATE demo)

# 关键：强制示例 main.cpp 的编译在 employee 的 CMI 生成之后执行（避免 Ninja 并行导致 import 找不到 CMI）。
# 这里用 OBJECT_DEPENDS 把“main.cpp 的 object 编译”与“模块 CMI 生成”建立显式依赖，
# 否则 Ninja 并行时可能先编 main.cpp，导致 `import xxx;` 找不到对应 gcm.cache/xxx.gcm。
set_source_files_properties("${EXAMPLE_MAIN_SRC}" PROPERTIES
	OBJECT_DEPENDS "${MODGCC_MODULE_CMIS};${MODGCC_MODULE_MAP_FILE}"
)

# 让 main_exe 目标在链接/构建阶段也依赖模块生成目标（双保险）。
add_dependencies(main_exe ${MODGCC_MODULE_TARGETS})

# 如果这一次构建执行了预编译标准头单元动作，则 main_exe 也依赖这些动作完成。
if(MODGCC_STD_DEPS)
	add_dependencies(main_exe ${MODGCC_STD_DEPS})
endif()

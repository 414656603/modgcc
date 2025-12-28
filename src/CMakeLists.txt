
set(SRC_ROOT "${CMAKE_SOURCE_DIR}")
set(GXX "${CMAKE_CXX_COMPILER}")

set(EMPLOYEE_SRC "${SRC_ROOT}/mymodules/employee.cppm")
set(MAIN_SRC "${SRC_ROOT}/src/main.cpp")
set(MAIN_EXE "${CMAKE_BINARY_DIR}/main.exe")

set(STDLIB_CMI_ROOT "D:/C++/gcc_prebuild_stdlib_gcm/15_2_0")
set(MODGCC_MODULE_MAPPER "-fmodule-mapper=|@g++-mapper-server -r ${STDLIB_CMI_ROOT} -f -n")

# 是否在构建时【自动】预编译标准库 header-unit（例如 <iostream>/<format>）。
#
# 默认 OFF：
# - 不在本工程根目录生成 std header-unit 的 CMI（不会创建/重建 gcm.cache/D-）。
# - 直接依赖 module-map 里配置的【共享 CMI 目录】下的 .gcm 文件（更快、更干净）。
#
# 何时需要 ON：
# - 你更新了 GCC/stdlib，或者共享 CMI 目录缺少所需的 .gcm（如 iostream.gcm/format.gcm）。
# - 想从“干净环境”一键生成并同步共享 CMI（本工程会先生成到 gcm.cache/D-，再拷贝到共享目录）。
#
# 如何开启（命令行）：
# - 配置阶段追加：-DMODGCC_PRECOMPILE_STDLIB=ON
#   例如：cmake --preset ninja-gcc -DMODGCC_PRECOMPILE_STDLIB=ON
option(MODGCC_PRECOMPILE_STDLIB "Precompile std header-units (iostream/format) into gcm.cache and sync them to the shared CMI directory" OFF)

set(MODGCC_STDLIB_STAMP "")


if(MODGCC_PRECOMPILE_STDLIB)
	set(GCM_CACHE_DIR "${SRC_ROOT}/gcm.cache")
	set(GCM_CACHE_STD_DIR "${GCM_CACHE_DIR}/D-")
	set(SHARED_STD_DIR "D:/C++/gcc_prebuild_stdlib_gcm/15_2_0/D-")
	set(STD_STAMP "${CMAKE_BINARY_DIR}/.stamp-std")

	add_custom_command(
		OUTPUT "${STD_STAMP}"
		COMMAND "${CMAKE_COMMAND}" -E rm -rf "${GCM_CACHE_DIR}"
		COMMAND "${GXX}" -std=c++20 -fmodules-ts -fdiagnostics-color=always -x c++-system-header iostream
		COMMAND "${GXX}" -std=c++20 -fmodules-ts -fdiagnostics-color=always -x c++-system-header format
		COMMAND "${CMAKE_COMMAND}" -E make_directory "${SHARED_STD_DIR}"
		COMMAND "${CMAKE_COMMAND}" -E copy_directory "${GCM_CACHE_STD_DIR}" "${SHARED_STD_DIR}"
		COMMAND "${CMAKE_COMMAND}" -E touch "${STD_STAMP}"
		WORKING_DIRECTORY "${SRC_ROOT}"
		VERBATIM
	)

	set(MODGCC_STDLIB_STAMP "${STD_STAMP}")

endif()

add_custom_command(
	OUTPUT "${MAIN_EXE}"
	COMMAND "${GXX}"
		-std=c++20
		-fmodules-ts
		-g
		-fdiagnostics-color=always
		-flang-info-module-cmi
		"${MODGCC_MODULE_MAPPER}"
		"${EMPLOYEE_SRC}"
		"${MAIN_SRC}"
		-o "${MAIN_EXE}"
	DEPENDS  "${EMPLOYEE_SRC}" "${MAIN_SRC}" ${MODGCC_STDLIB_STAMP}
	WORKING_DIRECTORY "${SRC_ROOT}"
	VERBATIM
)

add_custom_target(main_exe ALL DEPENDS "${MAIN_EXE}")

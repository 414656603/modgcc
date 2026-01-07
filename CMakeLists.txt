
cmake_minimum_required(VERSION 3.28)

project(modgcc_mapcmake LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(MODGCC_PRECOMPILE_STDLIB "Precompile std header-units (iostream/format) into gcm.cache and sync them to the shared CMI directory" OFF)
option(MODGCC_SUPPRESS_SYSTEM_HEADER_WARNINGS "Suppress warnings originating from system headers (e.g. libstdc++/Windows SDK)" OFF)
option(MODGCC_SUPPRESS_GCC_DANGLING_REFERENCE_WARNING "Suppress GCC -Wdangling-reference (often triggered in libstdc++ <format> header-units)" OFF)

# 共享的 std header-unit CMI 目录（module-map 会引用这里）。
set(MODGCC_SHARED_STD_DIR "D:/C++/gcc_prebuild_stdlib_gcm/15_2_0/D-")

# 为 CMake 构建生成 build 目录内的 module-map。
configure_file(
	"${CMAKE_SOURCE_DIR}/module-map.in"
	"${CMAKE_BINARY_DIR}/module-map"
	@ONLY
	NEWLINE_STYLE UNIX
)

set(MODGCC_MODULE_MAP_FILE "${CMAKE_BINARY_DIR}/module-map")
# 注意：MinGW g++ 在 Windows 下对 -fmodule-mapper=带盘符冒号的绝对路径有时会报
# "failed reading mapper"；这里统一使用 build 目录下的相对文件名。
set(MODGCC_MODULE_MAPPER_ARG "module-map")

# 这些 flag 需要同时用于：
# - 自定义命令（生成模块 CMI/obj）
# - 普通 target 编译（main.cpp）
set(MODGCC_COMMON_COMPILE_FLAGS
	-std=c++20
	-fmodules-ts
	-g
	-finput-charset=UTF-8
	-fexec-charset=UTF-8
	-fdiagnostics-color=always
	-flang-info-module-cmi
	-fmodule-mapper=${MODGCC_MODULE_MAPPER_ARG}
)

set(MODGCC_WARNING_FLAGS
	-Wall
	-Wextra
	-Wimplicit-fallthrough=3
)

# 可选：抑制编译系统头文件警告
if(MODGCC_SUPPRESS_SYSTEM_HEADER_WARNINGS)
	list(APPEND MODGCC_WARNING_FLAGS -Wno-system-headers)
endif()
# 可选：抑制 GCC 悬空引用警告（libstdc++ <format> 头文件单元中常触发该警告）
if(MODGCC_SUPPRESS_GCC_DANGLING_REFERENCE_WARNING)
	list(APPEND MODGCC_WARNING_FLAGS -Wno-dangling-reference)
endif()

# 可选：构建时自动预编译 std header-unit（iostream/format）并同步到共享目录。
set(MODGCC_STD_DEPS "")
if(MODGCC_PRECOMPILE_STDLIB)
	set(GCM_CACHE_DIR "${CMAKE_SOURCE_DIR}/gcm.cache")
	set(GCM_CACHE_STD_DIR "${GCM_CACHE_DIR}/D-")
	set(SHARED_STD_DIR "${MODGCC_SHARED_STD_DIR}")
	set(STD_STAMP "${CMAKE_BINARY_DIR}/.stamp-std")

	add_custom_command(
		OUTPUT "${STD_STAMP}"
		COMMAND "${CMAKE_COMMAND}" -E echo "[modgcc] MODGCC_PRECOMPILE_STDLIB=ON"
		COMMAND "${CMAKE_COMMAND}" -E echo "[modgcc] clean: ${GCM_CACHE_DIR}"
		COMMAND "${CMAKE_COMMAND}" -E rm -rf "${GCM_CACHE_DIR}"
		COMMAND "${CMAKE_COMMAND}" -E echo "[modgcc] precompile header-unit: <iostream>"
		COMMAND "${CMAKE_CXX_COMPILER}" -std=c++20 -fmodules-ts -fdiagnostics-color=always -x c++-system-header iostream
		COMMAND "${CMAKE_COMMAND}" -E echo "[modgcc] precompile header-unit: <format>"
		COMMAND "${CMAKE_CXX_COMPILER}" -std=c++20 -fmodules-ts -fdiagnostics-color=always -x c++-system-header format
		COMMAND "${CMAKE_COMMAND}" -E echo "[modgcc] precompile header-unit: <compare>"
		COMMAND "${CMAKE_CXX_COMPILER}" -std=c++20 -fmodules-ts -fdiagnostics-color=always -x c++-system-header compare
		COMMAND "${CMAKE_COMMAND}" -E echo "[modgcc] precompile header-unit: <array>"
		COMMAND "${CMAKE_CXX_COMPILER}" -std=c++20 -fmodules-ts -fdiagnostics-color=always -x c++-system-header array
		COMMAND "${CMAKE_COMMAND}" -E echo "[modgcc] precompile header-unit: <vector>"
		COMMAND "${CMAKE_CXX_COMPILER}" -std=c++20 -fmodules-ts -fdiagnostics-color=always -x c++-system-header vector
		COMMAND "${CMAKE_COMMAND}" -E echo "[modgcc] precompile header-unit: <optional>"
		COMMAND "${CMAKE_CXX_COMPILER}" -std=c++20 -fmodules-ts -fdiagnostics-color=always -x c++-system-header optional
		COMMAND "${CMAKE_COMMAND}" -E echo "[modgcc] precompile header-unit: <utility>"
		COMMAND "${CMAKE_CXX_COMPILER}" -std=c++20 -fmodules-ts -fdiagnostics-color=always -x c++-system-header utility
		COMMAND "${CMAKE_COMMAND}" -E echo "[modgcc] precompile header-unit: <initializer_list>"
		COMMAND "${CMAKE_CXX_COMPILER}" -std=c++20 -fmodules-ts -fdiagnostics-color=always -x c++-system-header initializer_list
		COMMAND "${CMAKE_COMMAND}" -E echo "[modgcc] precompile header-unit: <string>"
		COMMAND "${CMAKE_CXX_COMPILER}" -std=c++20 -fmodules-ts -fdiagnostics-color=always -x c++-system-header string
		COMMAND "${CMAKE_COMMAND}" -E echo "[modgcc] sync std CMI: ${GCM_CACHE_STD_DIR} -> ${SHARED_STD_DIR}"
		COMMAND "${CMAKE_COMMAND}" -E make_directory "${SHARED_STD_DIR}"
		COMMAND "${CMAKE_COMMAND}" -E copy_directory "${GCM_CACHE_STD_DIR}" "${SHARED_STD_DIR}"
		COMMAND "${CMAKE_COMMAND}" -E echo "[modgcc] ok: std header-units prepared"
		COMMAND "${CMAKE_COMMAND}" -E touch "${STD_STAMP}"
		WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
		VERBATIM
	)

	add_custom_target(stdlib_header_units DEPENDS "${STD_STAMP}")
	set(MODGCC_STD_DEPS stdlib_header_units)
endif()

add_subdirectory(mymodules)
add_subdirectory(src)
add_subdirectory(examples)

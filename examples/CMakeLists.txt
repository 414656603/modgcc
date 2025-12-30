
set(EXAMPLE_MAIN_SRC "${CMAKE_CURRENT_LIST_DIR}/main.cpp")

add_executable(main_exe
	${EXAMPLE_MAIN_SRC}
	"${CMAKE_SOURCE_DIR}/src/console_utf8.cpp"
	"${MODGCC_EMPLOYEE_OBJ}"
)
set_source_files_properties("${MODGCC_EMPLOYEE_OBJ}" PROPERTIES GENERATED TRUE)

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
set_source_files_properties("${EXAMPLE_MAIN_SRC}" PROPERTIES
	OBJECT_DEPENDS "${MODGCC_EMPLOYEE_CMI};${MODGCC_MODULE_MAP_FILE}"
)

add_dependencies(main_exe employee_module)

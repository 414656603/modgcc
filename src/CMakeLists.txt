
set(MAIN_SRC "${CMAKE_SOURCE_DIR}/src/main.cpp")

add_executable(main_exe "${MAIN_SRC}" "${MODGCC_EMPLOYEE_OBJ}")
set_source_files_properties("${MODGCC_EMPLOYEE_OBJ}" PROPERTIES GENERATED TRUE)

# 关闭 CMake 自带的（实验性）modules 扫描逻辑：它会额外注入一个 -fmodule-mapper=*.modmap，
# 从而覆盖我们手写的 module-map，导致 import <iostream>/<format> 找不到对应 header-unit CMI。
set_target_properties(main_exe PROPERTIES CXX_SCAN_FOR_MODULES OFF)

target_compile_options(main_exe PRIVATE
	${MODGCC_COMMON_COMPILE_FLAGS}
	${MODGCC_WARNING_FLAGS}
)

# 关键：强制 main.cpp 的编译在 employee 的 CMI 生成之后执行（避免 Ninja 并行导致 import 找不到 CMI）。
set_source_files_properties("${MAIN_SRC}" PROPERTIES
	OBJECT_DEPENDS "${MODGCC_EMPLOYEE_CMI};${MODGCC_MODULE_MAP_FILE}"
)

add_dependencies(main_exe employee_module)

set(SRC_ROOT "${CMAKE_SOURCE_DIR}")
set(GXX "${CMAKE_CXX_COMPILER}")

set(EMPLOYEE_SRC "${SRC_ROOT}/mymodules/employee.cppm")

# employee 模块的 CMI 输出位置由 module-map 决定（employee -> gcm.cache/employee.gcm）
set(EMPLOYEE_CMI "${CMAKE_BINARY_DIR}/gcm.cache/employee.gcm")
set(EMPLOYEE_OBJ "${CMAKE_CURRENT_BINARY_DIR}/employee.o")

add_custom_command(
	OUTPUT "${EMPLOYEE_OBJ}" "${EMPLOYEE_CMI}"
	COMMAND "${CMAKE_COMMAND}" -E make_directory "${CMAKE_BINARY_DIR}/gcm.cache"
	COMMAND "${GXX}"
		${MODGCC_COMMON_COMPILE_FLAGS}
		${MODGCC_WARNING_FLAGS}
		-c "${EMPLOYEE_SRC}"
		-o "${EMPLOYEE_OBJ}"
	DEPENDS "${MODGCC_MODULE_MAP_FILE}" "${EMPLOYEE_SRC}"
	WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
	COMMAND_EXPAND_LISTS
	VERBATIM
)

add_custom_target(employee_module DEPENDS "${EMPLOYEE_OBJ}" "${EMPLOYEE_CMI}")

if(MODGCC_STD_DEPS)
	add_dependencies(employee_module ${MODGCC_STD_DEPS})
endif()

set(MODGCC_EMPLOYEE_CMI "${EMPLOYEE_CMI}" PARENT_SCOPE)
set(MODGCC_EMPLOYEE_OBJ "${EMPLOYEE_OBJ}" PARENT_SCOPE)

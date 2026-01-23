
add_library(demo
	"${CMAKE_CURRENT_LIST_DIR}/demo/test_switch.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/demo/test_ternary_operator.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/demo/test_ThreewayComparisonOperator.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/demo/test_FunctionInvocation.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/demo/test_Array.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/demo/test_Vector.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/demo/test_Optional.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/demo/test_Loop.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/demo/test_InitializerList.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/demo/test_String.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/demo/testAll_Demos.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/demo/test_Reference.cpp"
)

# 关键：demo/testAll_Demos.cpp 内会 `import employee; import airline_ticket;`
# 需要确保对应 CMI 已生成，否则 Ninja 并行时可能先编译该 TU，导致 "imports must be built before being imported"。
set_source_files_properties("${CMAKE_CURRENT_LIST_DIR}/demo/testAll_Demos.cpp" PROPERTIES
	OBJECT_DEPENDS "${MODGCC_MODULE_CMIS};${MODGCC_MODULE_MAP_FILE}"
)

set_target_properties(demo PROPERTIES CXX_SCAN_FOR_MODULES OFF)

target_compile_options(demo PRIVATE
	${MODGCC_COMMON_COMPILE_FLAGS}
	${MODGCC_WARNING_FLAGS}
)

# 这句的意思是：目标 demo 在编译时会包含 include 目录下的头文件
target_include_directories(demo PUBLIC
	$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
)

# 如果这一次构建执行了预编译标准头单元动作，则 main_exe 也依赖这些动作完成。
if(MODGCC_STD_DEPS)
	add_dependencies(demo ${MODGCC_STD_DEPS})
endif()

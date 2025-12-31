
add_library(demo
	"${CMAKE_CURRENT_LIST_DIR}/demo/test_switch.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/demo/test_ternary_operator.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/demo/test_ThreewayComparisonOperator.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/demo/test_FunctionInvocation.cpp"
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

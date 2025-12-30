
add_library(demo
	"${CMAKE_CURRENT_LIST_DIR}/demo/test_switch.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/demo/test_ternary_operator.cpp"
)

set_target_properties(demo PROPERTIES CXX_SCAN_FOR_MODULES OFF)

target_compile_options(demo PRIVATE
	${MODGCC_COMMON_COMPILE_FLAGS}
	${MODGCC_WARNING_FLAGS}
)

target_include_directories(demo PUBLIC
	$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
)

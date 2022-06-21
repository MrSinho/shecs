cmake_minimum_required(VERSION 3.0)
add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=ON)

project(shecs-examples C)

set(SH_ECS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

#EXAMPLE 
add_executable(shecs-example shecs-example/src/shecs-example.c)
target_include_directories(shecs-example PUBLIC 
	${SH_ECS_INCLUDE_DIR}
)
set_target_properties(shecs-example PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)

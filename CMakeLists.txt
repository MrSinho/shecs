cmake_minimum_required(VERSION 3.0)
add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=ON)

project(ShECS C)

set(SH_ECS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

#EXAMPLE 
add_executable(ShECSExample Example/src/Example.c)
target_include_directories(ShECSExample PUBLIC 
	${SH_ECS_INCLUDE_DIR}
)

#OUTPUT
set_target_properties(ShECSExample PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)
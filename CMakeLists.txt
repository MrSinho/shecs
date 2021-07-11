cmake_minimum_required(VERSION 3.0)
add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=ON)

project(EZ_ECS C)

set(EZ_ECS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/EZ-ECS/include)

#EXAMPLE 
file(GLOB_RECURSE EZ_ECS_EXAMPLE_SRC Example/src/*.c)
add_executable(EZ_ECS_Example ${EZ_ECS_EXAMPLE_SRC})
target_include_directories(EZ_ECS_Example PUBLIC 
	${EZ_ECS_INCLUDE_DIR}
)

#OUTPUT
set_target_properties(EZ_ECS_Example PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)
cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=ON)

project(EZ_ECS VERSION 1.0)

#EXAMPLE 
file(GLOB_RECURSE EXAMPLE_SRC Example/*.cpp)
add_executable(Example ${EXAMPLE_SRC})
target_include_directories(Example PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

#OUTPUT
set_target_properties(Example PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)
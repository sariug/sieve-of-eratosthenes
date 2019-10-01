
cmake_minimum_required (VERSION 3.5)

project(sieve CXX)
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${TwinklebearDevLessons_SOURCE_DIR}/cmake")
set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17  -fopenmp -Wall -Ofast -funroll-loops -msse2 -ftree-vectorize -Wshadow -Wfloat-equal -Wextra -march=native ")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}")
find_package(MPI)


set ( CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR})

set ( EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set ( source_dir "${PROJECT_SOURCE_DIR}")
include_directories(${PROJECT_SOURCE_DIR} 
                    SYSTEM ${MPI_INCLUDE_PATH})

add_executable  (  sieve_of_eratosthenes sieve_of_eratosthenes.cpp ${HEADER_FILES}  )

target_link_libraries( sieve_of_eratosthenes ${MPI_CXX_LIBRARIES} )

#
#	Created by WW on 2019-6-27.
#	Copyright © WW. All rights reserved.
#

#required cmake version at least
cmake_minimum_required(VERSION 2.8)

#project name
project(Beta)

#Bring the header-files in directory /include into the project,
#so you don't need to include these header-files in the "add_executable/library" Command
#include_directories(include)

#add directory /src into the project, CMake will also execute the CMakeLists.txt file in /src,
#so you can use the files and libraries in /src
#add_subdirectory(src)

#CMAKE C/C++ compiler will use C++11	
add_compile_options(-std=c++11)

#add some new flags into original CXXFLAGS	
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

#compile and creat the executable file
#add_executable(beta main.cpp)

#define some variables representing the files
#GLOB and GLOB_RECURSE can recognize the Regular Expression *
file(GLOB LIB_HEADERS *.h)
file(GLOB LIB_SOURCES *.cpp *.c)

#compile and creat new library (SHARED or STATIC)
add_library(MYLIB STATIC ${LIB_HEADERS} ${LIB_SOURCES})

#add libraries into the EXTRA_LIBS
set(EXTRA_LIBS ${EXTRA_LIBS} MYLIB)

#define some variables representing the files
#GLOB and GLOB_RECURSE can recognize the Regular Expression *
file(GLOB HEADERS *.cuh)
file(GLOB SOURCES *.cu)

#find cuda packages
find_package(CUDA)

#add some new flags into original NVCC_FLAGS
set(CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS} -g -O3 -std=c++11 -cudart static -gencode arch=compute_60,code=sm_60")

#use CUDA C/C++ compiler nvcc to creat the executable file
cuda_add_executable(magnon.exe ${SOURCES} ${HEADERS})

#link the executable file with all libraries
target_link_libraries(magnon.exe ${EXTRA_LIBS})

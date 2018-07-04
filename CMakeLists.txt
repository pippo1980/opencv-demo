cmake_minimum_required(VERSION 3.8)
project(opencv_super_res_tool)


set(CMAKE_CXX_STANDARD 11)

#set(CMAKE_C_COMPILER "/usr/local/Cellar/gcc@4.9/4.9.4/bin/gcc-4.9")
#set(CMAKE_C_COMPILER "/usr/local/Cellar/gcc@4.9/4.9.4/bin/g++-4.9")
set (CMAKE_SHARED_LINKER_FLAGS "-Wl,--as-needed")

set(SOURCE_FILES main.cpp)
find_package( OpenCV REQUIRED )
link_directories(/usr/local/Cellar/opencv/3.4.1_1/lib)
link_libraries("opencv_superres")
link_libraries("opencv_highgui")


add_executable(opencv_super_res_tool ${SOURCE_FILES})

#include_directories(include)

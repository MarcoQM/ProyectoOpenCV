cmake_minimum_required(VERSION 3.5)

project(OpenCV_Example LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )


add_executable(OpenCV_Example  RGB.h Image.h main.cpp)

target_link_libraries(OpenCV_Example ${OpenCV_LIBS} )

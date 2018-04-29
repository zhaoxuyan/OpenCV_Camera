cmake_minimum_required(VERSION 3.8)
project(openCV_camera)

set(CMAKE_CXX_STANDARD 11)

#find_library(OpenCV)
find_package(OpenCV)

include_directories(${OpenCV_INCLUDE_DIRS})
set(CMAKE_CXX_STANDARD 11)

add_executable(openCV_camera openCV_ChineseWrite.cpp openCV_Canny.cpp openCV_FaceDetection.cpp openCV_FaceDetection_Blur.cpp)
target_link_libraries(openCV_camera ${OpenCV_LIBS})
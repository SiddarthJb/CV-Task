cmake_minimum_required(VERSION "3.10.2")

project(FaceDetection)

set(CMAKE_CXX_STANDARD 14)

find_package( OpenCV REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(FaceDetection main.cpp)

target_link_libraries(FaceDetection ${OpenCV_LIBS} )

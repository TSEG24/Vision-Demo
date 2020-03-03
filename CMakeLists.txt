cmake_minimum_required(VERSION 3.0)

project(VisionDemo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Used to tell visual studio to not put everything in top level directory
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Find OpenCV package
set(FIND_OPENCV_DIR
        ../../Libraries/opencv/build
        ${OPENCV_DIR}
        $ENV{OPENCV_DIR}/lib)

find_package(OpenCV REQUIRED PATHS ${FIND_OPENCV_DIR} NO_DEFAULT_PATH)

include_directories(OpenCV_INCLUDE_DIRS)
include_directories(AFTER dependencies)

add_executable(vision src/main.cpp src/main.cpp dependencies/opencv.h src/Application.cpp src/Application.h)

target_link_libraries(vision ${OpenCV_LIBS})

unset(COMPILE_STATIC)
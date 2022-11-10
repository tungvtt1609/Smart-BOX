cmake_minimum_required(VERSION 3.14)

project(face_detection_plugin LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_library(face_detection_plugin SHARED
  face_detection_plugin_global.h
  face_detection_plugin.cpp
  face_detection_plugin.h
  CvPluginInterface.h
)

target_link_libraries(face_detection_plugin PRIVATE Qt${QT_VERSION_MAJOR}::Core ${OpenCV_LIBS})

target_compile_definitions(face_detection_plugin PRIVATE FACE_DETECTION_PLUGIN_LIBRARY)


file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

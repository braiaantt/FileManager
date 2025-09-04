cmake_minimum_required(VERSION 3.14)

project(FileManager LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_library(FileManager STATIC
  src/filemanager.cpp
  include/filemanager.h
)

target_link_libraries(FileManager
    PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
)

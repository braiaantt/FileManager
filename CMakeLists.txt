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

target_include_directories(FileManager
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

install(TARGETS FileManager
    EXPORT FileManagerTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

install(DIRECTORY include/ DESTINATION include)

install(EXPORT FileManagerTargets
    FILE FileManagerTargets.cmake
    NAMESPACE FileManager::
    DESTINATION lib/cmake/FileManager
)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/FileManagerConfigVersion.cmake"
    VERSION 1.0.0
    COMPATIBILITY AnyNewerVersion
)

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/FileManagerConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/FileManagerConfig.cmake"
    @ONLY
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/FileManagerConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/FileManagerConfigVersion.cmake"
    DESTINATION lib/cmake/FileManager
)

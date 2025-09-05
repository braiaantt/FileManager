cmake_minimum_required(VERSION 3.14)

project(CommonUtils LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_library(CommonUtils STATIC

    src/ziputils.cpp
    src/jsonutils.cpp
    src/fileutils.cpp

    include/CommonUtils/fileutils.h
    include/CommonUtils/ziputils.h
    include/CommonUtils/jsonutils.h

)

target_link_libraries(CommonUtils
    PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
)

target_include_directories(CommonUtils
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/CommonUtils>
        $<INSTALL_INTERFACE:include>
)

install(TARGETS CommonUtils
    EXPORT CommonUtilsTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

install(DIRECTORY include/ DESTINATION include)

install(EXPORT CommonUtilsTargets
    FILE CommonUtilsTargets.cmake
    NAMESPACE CommonUtils::
    DESTINATION lib/cmake/CommonUtils
)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/CommonUtilsConfigVersion.cmake"
    VERSION 1.0.0
    COMPATIBILITY AnyNewerVersion
)

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/CommonUtilsConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/CommonUtilsConfig.cmake"
    @ONLY
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/CommonUtilsConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/CommonUtilsConfigVersion.cmake"
    DESTINATION lib/cmake/CommonUtils
)

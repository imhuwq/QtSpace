cmake_minimum_required(VERSION 3.10)
project(QtSpace)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS " -pthread ")
set(CMAKE_AUTOMOC ON)
set(CMAKE_PREFIX_PATH $ENV{QTDIR})
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

file(COPY File DESTINATION ${CMAKE_BINARY_DIR})

# packages required
find_package(Qt5Widgets)

# include dirs
include_directories(
        Lib
        Source
        ${Qt5Widgets_INCLUDE_DIRS})

# sub directories
add_subdirectory(Source/IO)
add_subdirectory(Source/Resource)
add_subdirectory(Source/GLRender)
add_subdirectory(Source/Application)
add_subdirectory(Source/Control)

# libraries
list(APPEND PRJ_LIBRARIES
        ${CMAKE_DL_LIBS}
        ${Qt5Widgets_LIBRARIES}
        glrender resource io control)

if (UNIX)
    list(APPEND PRJ_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/Lib/fbxsdk/libfbxsdk.so")
endif ()

add_executable(QtSpace Source/Application/main.cpp)
target_link_libraries(QtSpace application ${PRJ_LIBRARIES})

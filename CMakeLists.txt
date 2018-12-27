cmake_minimum_required(VERSION 3.10)
project(QtSpace)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS " -pthread ")
set(CMAKE_AUTOMOC ON)
set(CMAKE_PREFIX_PATH $ENV{QTDIR})
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# sub directories
add_subdirectory(Source/Resource)
add_subdirectory(Source/GLRender)
add_subdirectory(Source/Application)

# packages required
find_package(Qt5Widgets)

# include dirs
include_directories(Source)

# libraries
list(APPEND PRJ_LIBRARIES
        ${CMAKE_DL_LIBS}
        ${Qt5Widgets_LIBRARIES}
        "${CMAKE_CURRENT_SOURCE_DIR}/Lib/fbxsdk/libfbxsdk.a"
        glrender
        resource)

add_executable(QtSpace Source/Application/main.cpp)
target_link_libraries(QtSpace application ${PRJ_LIBRARIES})

file(COPY File DESTINATION ${CMAKE_BINARY_DIR})

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

# libraries
list(APPEND PRJ_LIBRARIES
        ${CMAKE_DL_LIBS}
        ${Qt5Widgets_LIBRARIES}
        glrender
        resource
        io
        "${CMAKE_CURRENT_SOURCE_DIR}/Lib/fbxsdk/libfbxsdk.so"
        )

add_executable(QtSpace Source/Application/main.cpp)
target_link_libraries(QtSpace application ${PRJ_LIBRARIES})

# model loader cli runner, for profile purpose
add_executable(model_loader Source/IO/ModelFileLoader/CommandLineTool.cpp)
target_include_directories(model_loader PRIVATE "/usr/local/include")
target_link_libraries(model_loader ${CMAKE_DL_LIBS} ${Qt5Widgets_LIBRARIES} io resource
        "${CMAKE_CURRENT_SOURCE_DIR}/Lib/fbxsdk/libfbxsdk.so"
        "/usr/local/lib/libtcmalloc_and_profiler.so")

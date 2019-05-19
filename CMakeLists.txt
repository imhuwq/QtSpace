cmake_minimum_required(VERSION 3.10)
project(QtSpace)

set(CMAKE_CXX_STANDARD 11)

if(UNIX)
	set(CMAKE_CXX_FLAGS " -pthread ")	
	set(PRJ_LIB "Lib/UNIX")
elseif(WIN32)
	set(PRJ_LIB "Lib/WIN32")
endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_PREFIX_PATH $ENV{QTDIR})
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

file(COPY File DESTINATION ${CMAKE_BINARY_DIR})

# packages required
find_package(Qt5Widgets)

# include dirs
include_directories(
        ${PRJ_LIB}
        Source
        ${Qt5Widgets_INCLUDE_DIRS})

# sub directories
add_subdirectory(Source/ModelLoader)
add_subdirectory(Source/Resource)
add_subdirectory(Source/GLRender)
add_subdirectory(Source/Application)
add_subdirectory(Source/Control)

# libraries
list(APPEND PRJ_LIBRARIES
        ${CMAKE_DL_LIBS}
        ${Qt5Widgets_LIBRARIES}
        glrender resource model_loader control)

if (UNIX)
    list(APPEND PRJ_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/Lib/UNIX/fbxsdk/libfbxsdk.so")
elseif(WIN32)
    list(APPEND PRJ_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/Lib/WIN32/fbxsdk/libfbxsdk.lib")
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/Lib/WIN32/fbxsdk/libfbxsdk.dll" DESTINATION ${CMAKE_BINARY_DIR})
MESSAGE(STATUS ${CMAKE_BINARY_DIR})
endif()

add_executable(QtSpace Source/Application/main.cpp)
target_link_libraries(QtSpace application ${PRJ_LIBRARIES})

add_executable(debug debug.cpp)
target_link_libraries(debug ${Qt5Widgets_LIBRARIES})

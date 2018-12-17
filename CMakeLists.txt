cmake_minimum_required(VERSION 3.13)
project(QtSpace)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS " -pthread ")
set(CMAKE_AUTOMOC ON)
set(CMAKE_PREFIX_PATH $ENV{QTDIR})

# things to be gathered
set(PRJ_INCLUDES "")
set(PRJ_LIBRARIES "")
set(PRJ_SOURCES "")

# packages required
find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5Widgets)

# include dirs
list(APPEND PRJ_INCLUDES Lib)
list(APPEND PRJ_INCLUDES Include)
list(APPEND PRJ_INCLUDES ${Qt5Core_INCLUDE_DIRS})
list(APPEND PRJ_INCLUDES ${Qt5Gui_INCLUDE_DIRS})
list(APPEND PRJ_INCLUDES ${Qt5Widgets_INCLUDE_DIRS})
list(REMOVE_DUPLICATES PRJ_INCLUDES)
include_directories(${PRJ_INCLUDES})

# libraries
list(APPEND PRJ_LIBRARIES ${Qt5Core_LIBRARIES})
list(APPEND PRJ_LIBRARIES ${Qt5Gui_LIBRARIES})
list(APPEND PRJ_LIBRARIES ${Qt5Widgets_LIBRARIES})
list(APPEND PRJ_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/Lib/fbxsdk/libfbxsdk.a")

# source files
file(GLOB_RECURSE PRJ_SOURCES1 Source/*.cpp)
file(GLOB_RECURSE PRJ_SOURCES2 Include/*.h)
list(APPEND PRJ_SOURCES ${PRJ_SOURCES1})
list(APPEND PRJ_SOURCES ${PRJ_SOURCES2})
list(REMOVE_DUPLICATES PRJ_SOURCES)

add_executable(QtSpace main.cpp ${PRJ_SOURCES})
target_link_libraries(QtSpace ${PRJ_LIBRARIES} ${CMAKE_DL_LIBS})

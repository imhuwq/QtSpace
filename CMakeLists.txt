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
list(APPEND PRJ_SOURCES Include/Application.h
        Include/MainWindow.h
        Source/MainWindow.cpp
        Include/GLRender/MainLoop.h
        Source/GLRender/MainLoop.cpp
        Include/Resource/Resource.h
        Include/Resource/Scene.h
        Include/Resource/Mesh.h
        Include/Resource/GraphNode/Node.h
        Include/Resource/GraphNode/Camera.h
        Include/Resource/GraphNode/Light.h
        Include/Resource/GraphNode/MeshInstance.h
        Include/Resource/Texture.h
        Include/Resource/Material.h
        Include/Resource/Model.h
        Include/GLRender/SceneRender.h
        Include/GLRender/NodeRender.h
        Include/GLRender/Shader.h
        )

add_executable(QtSpace main.cpp ${PRJ_SOURCES})
target_link_libraries(QtSpace ${PRJ_LIBRARIES} ${CMAKE_DL_LIBS})

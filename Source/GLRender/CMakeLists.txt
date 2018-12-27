find_package(Qt5Widgets)

list(APPEND GLRENDER_SOURCES
        MainLoop.h
        MainLoop.cpp
        SceneRender.h
        SceneRender.cpp
        MeshInstanceRender.h
        MeshInstanceRender.cpp
        Shader.h
        )
add_library(glrender STATIC ${GLRENDER_SOURCES})


list(APPEND GLRENDER_INCLUDES
        "${CMAKE_SOURCE_DIR}/Source"
        ${Qt5Widgets_INCLUDE_DIRS}
        )
message(STATUS ${CMAKE_SOURCE_DIR}/Source)
target_include_directories(glrender PRIVATE ${GLRENDER_INCLUDES})

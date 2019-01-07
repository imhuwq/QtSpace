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

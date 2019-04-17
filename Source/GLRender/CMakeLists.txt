find_package(Qt5Widgets)

list(APPEND GLRENDER_SOURCES
        MainLoop.h
        MainLoop.cpp
		SceneAnimator.h
		SceneAnimator.cpp
        SceneRender.h
        SceneRender.cpp
        MeshInstanceRender.h
        MeshInstanceRender.cpp
        )

add_library(glrender STATIC ${GLRENDER_SOURCES})

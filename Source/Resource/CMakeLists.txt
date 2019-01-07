find_package(Qt5Widgets)

list(APPEND RESOURCE_SOURCES
        Resource.h
        Resource.cpp
        Texture.h
        Texture.cpp
        Material.h
        Material.cpp
        Mesh.h
        Mesh.cpp
        Model.h
        Model.cpp
        Scene.h
        Scene.cpp
        GraphNode/Node.h
        GraphNode/Node.cpp
        GraphNode/Camera.h
        GraphNode/Camera.cpp
        GraphNode/Light.h
        GraphNode/Light.cpp
        GraphNode/MeshInstance.h
        GraphNode/MeshInstance.cpp
        )

add_library(resource STATIC ${RESOURCE_SOURCES})

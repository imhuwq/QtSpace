find_package(Qt5Widgets)

list(APPEND RESOURCE_SOURCES
        Resource.h
        Resource.cpp
        Texture.h
        Texture.cpp
        Material.h
        Material.cpp
		Cubemap.h
		Cubemap.cpp
		Skybox.h
		Skybox.cpp
        Mesh.h
        Mesh.cpp
        Scene.h
        Scene.cpp
        GraphNode/Node.h
        GraphNode/Node.cpp
        GraphNode/Camera.h
        GraphNode/Camera.cpp
        GraphNode/Light/Light.h
        GraphNode/Light/Light.cpp
        GraphNode/Light/DotLight.h
        GraphNode/Light/DotLight.cpp
        GraphNode/Light/SpotLight.h
        GraphNode/Light/SpotLight.cpp
        GraphNode/Light/DirectionLight.h
        GraphNode/Light/DirectionLight.cpp
        GraphNode/MeshInstance.h
        GraphNode/MeshInstance.cpp
        )

add_library(resource STATIC ${RESOURCE_SOURCES})

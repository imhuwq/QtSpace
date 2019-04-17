find_package(Qt5Widgets)

list(APPEND IO_SOURCES
        ModelFileLoader/ModelFileLoader.h
        ModelFileLoader/ModelFileLoader.cpp
        ModelFileLoader/FBXFileLoader.h
        ModelFileLoader/FBXFileLoader.cpp
		ModelFileLoader/VertexPack.h
		ModelFileLoader/VertexPack.cpp
		ModelFileLoader/VertexTable.h
		ModelFileLoader/VertexTable.cpp
		ModelFileLoader/VertexContext.h
		ModelFileLoader/VertexSemantic.h
		ModelFileLoader/VertexSemantic.cpp
        )

add_library(io STATIC ${IO_SOURCES})

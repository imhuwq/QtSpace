find_package(Qt5Widgets)

list(APPEND MODEL_LOADER_SOURCES
        ModelFileLoader.h
        ModelFileLoader.cpp
        FBXFileLoader.h
        FBXFileLoader.cpp
        VertexPack.h
        VertexPack.cpp
        VertexTable.h
        VertexTable.cpp
        VertexContext.h
        VertexSemantic.h
        VertexSemantic.cpp
        )

add_library(model_loader STATIC ${MODEL_LOADER_SOURCES})

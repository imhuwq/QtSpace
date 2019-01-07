find_package(Qt5Widgets)

list(APPEND IO_SOURCES
        ModelFileLoader/ModelFileLoader.h
        ModelFileLoader/ModelFileLoader.cpp
        ModelFileLoader/FBXFileLoader.h
        ModelFileLoader/FBXFileLoader.cpp
        )

add_library(io STATIC ${IO_SOURCES})

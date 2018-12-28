find_package(Qt5Widgets)

list(APPEND IO_SOURCES
        ModelFileLoader/ModelFileLoader.h
        ModelFileLoader/ModelFileLoader.cpp
        ModelFileLoader/FBXFileLoader.h
        ModelFileLoader/FBXFileLoader.cpp
        )
add_library(io STATIC ${IO_SOURCES})

list(APPEND GLRENDER_INCLUDES
        "${CMAKE_SOURCE_DIR}/Lib"
        "${CMAKE_SOURCE_DIR}/Source"
        ${Qt5Widgets_INCLUDE_DIRS}
        )
message(STATUS ${CMAKE_SOURCE_DIR}/Source)
target_include_directories(io PRIVATE ${GLRENDER_INCLUDES})

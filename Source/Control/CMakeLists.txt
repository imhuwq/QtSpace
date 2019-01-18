find_package(Qt5Widgets)

list(APPEND CONTROL_SOURCES
        Controller.h
        Controller.cpp
        )

add_library(control STATIC ${CONTROL_SOURCES})

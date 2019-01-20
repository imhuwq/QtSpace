find_package(Qt5Widgets)

list(APPEND CONTROL_SOURCES
        State.h
        State.cpp
        Controller.h
        Controller.cpp
        )

add_library(control STATIC ${CONTROL_SOURCES})

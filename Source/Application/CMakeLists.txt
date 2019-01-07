find_package(Qt5Widgets)

list(APPEND APPLICATION_SOURCES
        Application.h
        Application.cpp
        MainWindow.h
        MainWindow.cpp
        )

add_library(application STATIC ${APPLICATION_SOURCES})

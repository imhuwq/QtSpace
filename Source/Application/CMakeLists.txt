find_package(Qt5Widgets)

list(APPEND APPLICATION_SOURCES
        Application.h
        Application.cpp
        MainWindow.h
        MainWindow.cpp
        )
add_library(application STATIC ${APPLICATION_SOURCES})

list(APPEND APPLICATION_INCLUDES
        "${CMAKE_SOURCE_DIR}/Source"
        ${Qt5Widgets_INCLUDE_DIRS}
        )
target_include_directories(application PRIVATE ${APPLICATION_INCLUDES})

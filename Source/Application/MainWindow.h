#ifndef QTSPACE_MAINWINDOW_H
#define QTSPACE_MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>

#include "GLRender/MainLoop.h"
#include "Control/Controller.h"

class MainWindow : public QMainWindow {
Q_OBJECT
public:
    MainWindow(ControllerPtr controller, QWidget *parent = nullptr);

    ~MainWindow() override = default;

private:
    MainLoop* gl_widget_ = nullptr;
    ControllerPtr controller_ = nullptr;

    void InitWindow();

    void InitGL();
};

#endif //QTSPACE_MAINWINDOW_H

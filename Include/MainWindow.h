#ifndef QTSPACE_MAINWINDOW_H
#define QTSPACE_MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>

#include "GLRender/MainLoop.h"

class MainWindow : public QMainWindow {
Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr) {
        InitWindow();
        InitGL();
    }

    ~MainWindow() override = default;

private:
    MainLoop *gl_widget_ = nullptr;

    void InitWindow();

    void InitGL();
};

#endif //QTSPACE_MAINWINDOW_H

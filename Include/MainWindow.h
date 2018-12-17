#ifndef QTSPACE_MAINWINDOW_H
#define QTSPACE_MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>

class MainWindow : public QMainWindow {
Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr) {
        InitWindow();
    }

    ~MainWindow() override = default;

private:
    void InitWindow();
};

#endif //QTSPACE_MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "header/scene.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionRestart_triggered();
    void on_actionQuit_triggered();
    void gameOver(long score);

    void on_actionAIPlay_triggered();

private:
    Ui::MainWindow *ui;
    Scene* scene;
};
#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "board.h"

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

private:
    Ui::MainWindow *ui;
    Board* board;
};
#endif // MAINWINDOW_H

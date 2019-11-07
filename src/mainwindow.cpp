#include "header/mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), scene(new Scene(4, this))
{
    ui->setupUi(this);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->scene()->setSceneRect(0, 0, 800, 600);
    ui->graphicsView->setDragMode(QGraphicsView::NoDrag);
    ui->graphicsView->scale(1, -1);
    ui->graphicsView->setBackgroundBrush(QColor("#faf8ef"));

    scene->initBoardGame();
    connect(scene, &Scene::gameOver, this, &MainWindow::gameOver);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionRestart_triggered()
{
    QMessageBox::StandardButton message_box;
    message_box = QMessageBox::question(this, "Restart game", "Do you really want to restart game?", QMessageBox::No | QMessageBox::Yes);
    if (message_box == QMessageBox::Yes) {
        scene->reset();
    }
}

void MainWindow::on_actionQuit_triggered()
{
    QMessageBox::StandardButton message_box;
    message_box = QMessageBox::question(this, "Quit game", "Do you really want to quit game?", QMessageBox::No | QMessageBox::Yes);
    if (message_box == QMessageBox::Yes) {
        qApp->exit();
    }
}

void MainWindow::gameOver(long score)
{
    QMessageBox::StandardButton message_box;
    message_box = QMessageBox::question(this, "Game over", QString("Your score is: %1. Play another game?").arg(score), QMessageBox::No | QMessageBox::Yes);
    if (message_box == QMessageBox::Yes) {
        scene->reset();
    }
    else {
        qApp->exit();
    }
}

void MainWindow::on_actionAIPlay_triggered()
{
    scene->aiPlay();
}

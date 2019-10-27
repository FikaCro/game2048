#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "board.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), board(new Board(4, this))
{
    ui->setupUi(this);

    ui->graphicsView->setScene(board);
    ui->graphicsView->scene()->setSceneRect(0, 0, 800, 600);
    ui->graphicsView->setDragMode(QGraphicsView::NoDrag);
    ui->graphicsView->scale(1, -1);
    ui->graphicsView->setBackgroundBrush(QColor("#faf8ef"));

    board->initBoardGame();

    connect(board, &Board::gameOver, this, &MainWindow::gameOver);
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
        board->reset();
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
        board->reset();
    }
    else {
        qApp->exit();
    }
}

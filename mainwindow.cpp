#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "board.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), board(new Board(4, this))
{
    ui->setupUi(this);

    ui->graphicsView->setScene(board);
    ui->graphicsView->scene()->setSceneRect(0, 0, 800, 600);
    ui->graphicsView->setDragMode(QGraphicsView::NoDrag);
    ui->graphicsView->scale(1, -1);

    board->initBoardGame();
}

MainWindow::~MainWindow()
{
    delete ui;
}


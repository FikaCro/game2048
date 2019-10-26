#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "board.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), board_scene(new Board(4, this))
{
    ui->setupUi(this);

    ui->graphicsView->setScene(board_scene);
    ui->graphicsView->scene()->setSceneRect(0, 0, 800, 600);
    ui->graphicsView->setDragMode(QGraphicsView::NoDrag);
    ui->graphicsView->scale(1, -1);

    board_scene->initBoardGame();
}

MainWindow::~MainWindow()
{
    delete ui;
}


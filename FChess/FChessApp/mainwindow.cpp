#include "mainwindow.h"
#include "Widgets/boardwidget.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	setCentralWidget(new BoardWidget(this));
}

MainWindow::~MainWindow()
{
	delete ui;
}

#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "gitparentrequest.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->BlameSlot->addWidget(blameView);

    GitParentRequest reqHandler;

    ui->label->setText(reqHandler.GetStatus());

    auto users = reqHandler.GetAuthors();

    blameView->AddUsers(users);
}

MainWindow::~MainWindow()
{
    delete ui;
}

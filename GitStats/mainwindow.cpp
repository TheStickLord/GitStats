#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "gitparentrequest.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->BlameSlot->addWidget(blameView);
    ui->Status_2->setText(reqHandler.GetStatus());

    auto users = reqHandler.GetAuthors();
    blameView->AddUsers(users);

    connect(ui->actionFolder,
            &QAction::triggered,
            this,
            &MainWindow::Update);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Update() {
    QString dir = QFileDialog::getExistingDirectory();

    reqHandler.SetDirectory(dir);

    auto users = reqHandler.GetAuthors();
    blameView->AddUsers(users);

    ui->Status_2->setText(reqHandler.GetStatus());
}

void MainWindow::Pull() {
    QString pullsStatus = reqHandler.PullRepo();
    this->Update();
    ui->PullsStatus->setText(pullsStatus);
}
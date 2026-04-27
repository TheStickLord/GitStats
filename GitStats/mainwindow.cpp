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
    blameView->Update();
    ui->FileSlot->addWidget(fileBlameView);
    fileBlameView->Update();

    ui->Status_2->setText(reqHandler.GetStatus());

    connect(ui->actionFolder,
            &QAction::triggered,
            this,
            &MainWindow::Update);

    connect(ui->actionPull,
            &QAction::triggered,
            this,
            &MainWindow::Pull);

    connect(ui->pushButton, &QPushButton::clicked,
            this, [this]{ui->Status_2->setText(reqHandler.GetStatus());});
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Update() {
    QString dir = QFileDialog::getExistingDirectory();

    reqHandler.SetDirectory(dir);

    ui->Status_2->setText(reqHandler.GetStatus());

    this->fileBlameView->Update();
    this->blameView->Update();
}

void MainWindow::Pull() {
    ui->PullsStatus->setText(reqHandler.PullRepo());
}
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
    QString userText = "";

    for (auto user : users) {
        userText.append(user.Name);
        userText.append(" ");
        userText.append(QString::number(user.Commits));
        userText.append("\n");
        qDebug("Test1");
    }

    ui->label_2->setText(userText);
}

MainWindow::~MainWindow()
{
    delete ui;
}

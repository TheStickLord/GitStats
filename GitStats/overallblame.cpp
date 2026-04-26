#include "overallblame.h"
#include "ui_overallblame.h"

OverallBlame::OverallBlame(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::OverallBlame)
{
    ui->setupUi(this);

    ui->horizontalLayout->addWidget(this->chart);
}

OverallBlame::~OverallBlame()
{
    delete ui;
}

void OverallBlame::AddUsers(std::vector<User> users)
{
    QString userText = "";
    double total = 0;

    for (auto user : users) {
        // Generate Text
        userText.append(user.Name);
        userText.append(" ");
        userText.append(QString::number(user.Commits));
        userText.append("\n");
        qDebug("Test1");

        // Generate Total
        total += user.Commits;
    }

    ui->label_2->setText(userText);

    // Set Donut

    for (auto user : users) {
        chart->addSlice(user.Name, double(user.Commits * 100)/total);
    }
}

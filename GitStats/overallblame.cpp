#include "overallblame.h"
#include "ui_overallblame.h"

OverallBlame::OverallBlame(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::OverallBlame)
{
    ui->setupUi(this);
}

OverallBlame::~OverallBlame()
{
    delete ui;
}

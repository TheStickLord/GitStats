#include "circularchart.h"
#include "ui_circularchart.h"

CircularChart::CircularChart(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CircularChart)
{
    ui->setupUi(this);
}

CircularChart::~CircularChart()
{
    delete ui;
}

void CircularChart::SetUsers(std::vector<User> users)
{
    this->values = users;
    update();
}

void CircularChart::AddUser(User user)
{
    this->values.push_back(user);
    update();
}

void CircularChart::Clear()
{
    this->values.clear();
    update();
}



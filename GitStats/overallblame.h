#ifndef OVERALLBLAME_H
#define OVERALLBLAME_H

#include "donutchart.h"
#include "user.h"
#include <QWidget>

namespace Ui {
class OverallBlame;
}

class OverallBlame : public QWidget
{
    Q_OBJECT

public:
    explicit OverallBlame(QWidget *parent = nullptr);
    ~OverallBlame();

    void AddUsers(std::vector<User> users);

private:
    Ui::OverallBlame *ui;

    DonutChart* chart = new DonutChart();;
};

#endif // OVERALLBLAME_H

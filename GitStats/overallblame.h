#ifndef OVERALLBLAME_H
#define OVERALLBLAME_H

#include "circularchart.h"
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

    void Clear();

private:
    Ui::OverallBlame *ui;

    CircularChart* chart = new CircularChart(this);
};

#endif // OVERALLBLAME_H

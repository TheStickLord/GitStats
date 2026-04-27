#ifndef OVERALLBLAME_H
#define OVERALLBLAME_H

#include "circularchart.h"
#include "gitparentrequest.h"
#include "user.h"
#include <QWidget>

namespace Ui {
class OverallBlame;
}

class OverallBlame : public QWidget
{
    Q_OBJECT

public:
    explicit OverallBlame(QWidget *parent = nullptr, GitParentRequest* reqHandler = nullptr);
    ~OverallBlame();

    void Update();
    void UpdateFile(QString file);

    void AddUsers(std::vector<User> users);
    void Clear();

private:
    Ui::OverallBlame *ui;

    GitParentRequest* reqHandler;

    CircularChart* chart = new CircularChart(this);
};

#endif // OVERALLBLAME_H

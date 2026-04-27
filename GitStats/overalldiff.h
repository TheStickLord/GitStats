#ifndef OVERALLDIFF_H
#define OVERALLDIFF_H

#include "gitparentrequest.h"
#include <QWidget>

namespace Ui {
class OverallDiff;
}

class OverallDiff : public QWidget
{
    Q_OBJECT

public:
    explicit OverallDiff(QWidget *parent = nullptr, GitParentRequest* reqHandler = nullptr);
    ~OverallDiff();

    void Update();
    void UpdateFile(QString file);

private:
    Ui::OverallDiff *ui;

    GitParentRequest* reqHandler;

    int currentRow = 2;

    void addUser(User user);
    void clear();
};

#endif // OVERALLDIFF_H

#ifndef OVERALLBLAME_H
#define OVERALLBLAME_H

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

private:
    Ui::OverallBlame *ui;
};

#endif // OVERALLBLAME_H

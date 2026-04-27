#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gitparentrequest.h"
#include "overallblame.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    OverallBlame* blameView = new OverallBlame();

    GitParentRequest reqHandler;

public slots:
    void Update();
    void Pull();
};
#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "fileblame.h"
#include "gitparentrequest.h"
#include "overallblame.h"
#include "overalldiff.h"
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

    GitParentRequest reqHandler;

    OverallBlame* blameView = new OverallBlame(this, &reqHandler);
    OverallDiff* diffView = new OverallDiff(this, &reqHandler);

    FileBlame* fileBlameView = new FileBlame(this, &reqHandler);

public slots:
    void Update();
    void Pull();
};
#endif // MAINWINDOW_H

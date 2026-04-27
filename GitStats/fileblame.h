#ifndef FILEBLAME_H
#define FILEBLAME_H

#include "gitparentrequest.h"
#include "overallblame.h"
#include "overalldiff.h"
#include <QWidget>

namespace Ui {
class FileBlame;
}

class FileBlame : public QWidget
{
    Q_OBJECT

public:
    explicit FileBlame(QWidget *parent = nullptr, GitParentRequest* reqHandler = nullptr);
    ~FileBlame();

    void Update();

private:
    Ui::FileBlame *ui;

    GitParentRequest* reqHandler;

    OverallBlame* blameView = new OverallBlame(this, reqHandler);
    OverallDiff* diffView = new OverallDiff(this, reqHandler);

    QStringList selectedOptions = {};

    void showPopup();

    void removeUnecessaryItems();

    void getTypes(QStringList files);

    QStringList fileTypes = {};
};

#endif // FILEBLAME_H

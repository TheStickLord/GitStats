#include "overalldiff.h"
#include "ui_overalldiff.h"

OverallDiff::OverallDiff(QWidget *parent, GitParentRequest *reqHandler)
    : QWidget(parent)
    , ui(new Ui::OverallDiff)
    , reqHandler(reqHandler)
{
    ui->setupUi(this);
}

OverallDiff::~OverallDiff()
{
    delete ui;
}

void OverallDiff::Update()
{
    clear();
    std::vector<User> users = reqHandler->GetDiffByUser();

    std::sort(users.begin(), users.end());
    std::reverse(users.begin(), users.end());

    for (auto user : users) {
        addUser(user);
    }

    update();
}

void OverallDiff::UpdateFile(QString file)
{
    clear();
    std::vector<User> users = reqHandler->GetDiffByUserFile(file);

    std::sort(users.begin(), users.end());
    std::reverse(users.begin(), users.end());

    for (auto user : users) {
        addUser(user);
    }

    update();
}

void OverallDiff::addUser(User user)
{
    QLabel* UserName = new QLabel;
    UserName->setText(user.Name);

    QLabel* UserAdd = new QLabel;
    UserAdd->setText(QString::number(user.Added));

    QLabel* UserRem = new QLabel;
    UserRem->setText(QString::number(user.Deleted));

    QFrame* l1 = new QFrame;
    l1->setFrameShape(QFrame::VLine);

    QFrame* l2 = new QFrame;
    l2->setFrameShape(QFrame::VLine);

    ui->gridLayout->addWidget(UserName, currentRow, 0);
    ui->gridLayout->addWidget(l1, currentRow, 1);
    ui->gridLayout->addWidget(UserAdd, currentRow, 2);
    ui->gridLayout->addWidget(l2, currentRow, 3);
    ui->gridLayout->addWidget(UserRem, currentRow, 4);

    currentRow++;
}

void OverallDiff::clear()
{
    currentRow = 2;

    while (ui->gridLayout->count() > 10)
    {
        QLayoutItem* item = ui->gridLayout->takeAt(10);

        if (!item)
            break;

        QWidget* widget = item->widget();

        if (widget)
            widget->deleteLater();

        delete item;
    }
}

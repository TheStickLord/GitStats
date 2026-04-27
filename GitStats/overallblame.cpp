#include "overallblame.h"
#include "ui_overallblame.h"
#include <qlabel.h>

OverallBlame::OverallBlame(QWidget *parent, GitParentRequest* reqHandler)
    : QWidget(parent)
    , ui(new Ui::OverallBlame)
    , reqHandler(reqHandler)
{
    ui->setupUi(this);

    ui->ChartSlot->insertWidget(0, chart);
}

OverallBlame::~OverallBlame()
{
    delete ui;
}

void OverallBlame::Update()
{
    AddUsers(reqHandler->GetAuthors());
}

void OverallBlame::UpdateFile(QString file)
{
    AddUsers(reqHandler->GetAuthorsFile(file));
}

void OverallBlame::AddUsers(std::vector<User> users)
{
    Clear();

    std::sort(users.begin(), users.end());
    std::reverse(users.begin(), users.end());

    chart->SetUsers(users); // important

    // Check for users
    if (users.size() < 1) {
        QLabel* label = new QLabel();
        label->setText("No Git data available");
        ui->Users->addWidget(label);
    }

    // Calculate size ---------------------------
    double total = 0;
    for (const auto &user : users) {
        total += user.Commits;
    }

    // Add users
    for (int i = 0; i < users.size(); i++) {
        auto user = users[i];
        QColor color = QColor::fromHsv(
            (i * 360) / users.size(), // hue
            180,            // saturation
            220             // value/brightness
            );

        QString mailChopped = user.Email;
        int maxLength = 30;
        if (mailChopped.length() > maxLength) {
            mailChopped.chop(-(maxLength - mailChopped.length()));
            mailChopped.append("...");
        }

        QString userString = QString("%%1 | %2 Commit(s) | %3 <%4>").arg(
            QString::number(std::round(double(user.Commits)*1000/total)/10),
            QString::number(user.Commits),
            user.Name,
            mailChopped);

        QLabel* label = new QLabel();
        label->setText(userString);
        label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        label->setStyleSheet(
            QString("QLabel {"
                    "color: %1;"
                    "}")
                .arg(color.name())
            );
        ui->Users->addWidget(label);
    }
}

void OverallBlame::Clear()
{
    while (ui->Users->count() > 0) {
        auto item = ui->Users->takeAt(0);
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }
}

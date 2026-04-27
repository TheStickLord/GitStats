#include "fileblame.h"
#include "gitparentrequest.h"
#include "ui_fileblame.h"
#include "checkboxdialog.h"

FileBlame::FileBlame(QWidget *parent, GitParentRequest* reqHandler)
    : QWidget(parent)
    , ui(new Ui::FileBlame)
    , reqHandler(reqHandler)
{
    ui->setupUi(this);

    QStringList options = reqHandler->GetFiles();

    ui->comboBox->addItems(options);
    ui->BlameSlot->addWidget(blameView);

    blameView->UpdateFile(ui->comboBox->currentText());

    connect(ui->comboBox, &QComboBox::currentTextChanged, this, [this](const QString text){blameView->UpdateFile(text);});
    connect(ui->filterButton, &QPushButton::clicked, this, &FileBlame::showPopup);
}

FileBlame::~FileBlame()
{
    delete ui;
}

void FileBlame::Update()
{
    QStringList options = this->reqHandler->GetFiles();
    selectedOptions.clear();

    ui->comboBox->clear();
    ui->comboBox->addItems(options);
    getTypes(options);

    blameView->UpdateFile(ui->comboBox->currentText());
}

void FileBlame::getTypes(QStringList files)
{
    this->fileTypes.clear();

    for (QString &file : files) {
        QString type = "";

        auto stringSplit = file.split('.');
        if (stringSplit.length() > 1) {
            type = stringSplit[stringSplit.size() - 1];
        }

        if (!this->fileTypes.contains(type)) {
            fileTypes.append(type);
        }
    }
}

void FileBlame::showPopup()
{
    Update();

    CheckboxDialog dialog(nullptr, fileTypes);

    dialog.exec();

    dialog.accept();

    selectedOptions = dialog.GetSelectedOptions();
    removeUnecessaryItems();
}

void FileBlame::removeUnecessaryItems()
{
    if (selectedOptions.empty() || selectedOptions[0] == "%all%") {
        return;
    }

    for (int i = ui->comboBox->count() - 1; i >= 0; --i) {
        QString text = ui->comboBox->itemText(i);
        QStringList splitString = text.split(".");

        if (splitString.length() > 1) {
            QString extension = splitString.last(); // usually safer than [1]

            if (!selectedOptions.contains(extension)) {
                ui->comboBox->removeItem(i);
            }
        }
    }
}

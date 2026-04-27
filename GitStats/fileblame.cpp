#include "fileblame.h"
#include "gitparentrequest.h"
#include "ui_fileblame.h"

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
}

FileBlame::~FileBlame()
{
    delete ui;
}

void FileBlame::Update()
{
    QStringList options = this->reqHandler->GetFiles();

    ui->comboBox->clear();
    ui->comboBox->addItems(options);

    blameView->UpdateFile(ui->comboBox->currentText());
}

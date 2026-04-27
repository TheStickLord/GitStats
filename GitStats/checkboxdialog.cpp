#include "checkboxdialog.h"
#include "ui_checkboxdialog.h"
#include <qcheckbox.h>

CheckboxDialog::CheckboxDialog(QWidget *parent, QStringList options)
    : QDialog(parent)
    , ui(new Ui::CheckboxDialog)
{
    ui->setupUi(this);

    setWindowTitle(" ");
    setWindowIcon(QIcon(":/images/GearIcon.png"));

    for (const QString &option : std::as_const(options)) {
        addOption(option);
    }

    connect(ui->checkBox, &QCheckBox::clicked, this, [this](bool checked) {
        if (checked) {
            for (int i = 0; i < ui->OptionSlots->count(); i++)
            {
                QWidget* option = ui->OptionSlots->itemAt(i)->widget();

                option->setEnabled(false);
            }
        } else {
            for (int i = 0; i < ui->OptionSlots->count(); i++)
            {
                QWidget* option = ui->OptionSlots->itemAt(i)->widget();

                option->setEnabled(true);
            }
        }
    });
}

CheckboxDialog::~CheckboxDialog()
{
    delete ui;
}

void CheckboxDialog::accept() {
    selected.clear();

    if (ui->checkBox->isChecked()) {
        selected.append("%all%");
        QDialog::accept();
        return;
    }

    for (int i = 0; i < ui->OptionSlots->count(); i++)
    {
        QWidget* option = ui->OptionSlots->itemAt(i)->widget();

        QCheckBox* box = qobject_cast<QCheckBox*>(option);

        if(box && box->isChecked())   // only checked ones
        {
            selected.append(box->text());
        }
    }

    QDialog::accept(); // close dialog properly
}

void CheckboxDialog::addOption(QString option)
{
    QCheckBox* optionBox = new QCheckBox();
    optionBox->setText(option);
    ui->OptionSlots->addWidget(optionBox);
}

#ifndef CHECKBOXDIALOG_H
#define CHECKBOXDIALOG_H

#include <QDialog>

namespace Ui {
class CheckboxDialog;
}

class CheckboxDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CheckboxDialog(QWidget *parent = nullptr, QStringList options = {});
    ~CheckboxDialog();

    void accept() override;

    QStringList GetSelectedOptions() {return selected;}

private:
    Ui::CheckboxDialog *ui;

    QStringList selected = {};

    void addOption(QString option);
};

#endif // CHECKBOXDIALOG_H

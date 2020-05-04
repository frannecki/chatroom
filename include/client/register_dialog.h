#ifndef REGISTER_DIALOG_H
#define REGISTER_DIALOG_H
#include "ui_register_dialog.h"
#include <QCloseEvent>
#include <QSettings>
#include <QMessageBox>
#include <QDialog>

#include "utils.h"

namespace Ui{
    class registerDialog;
}

class registerDialog : public QDialog{
    Q_OBJECT

public:
    explicit registerDialog(QWidget* parent = 0);
    ~registerDialog();

signals:
    void registerRequested(std::string, std::string);

public slots:
    void accept();
    // reject() closes widget by default. There is no need to override
    void on_registration_succeeded();
    void on_registration_failed();
    void on_signupRequested();

private:
    Ui::registerDialog *ui;
    void WriteSettings();
    void ReadSettings();
};

#endif
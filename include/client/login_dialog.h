#ifndef LOGIN_DIALOG_H
#define LOGIN_DIALOG_H
#include "ui_login_dialog.h"
#include "register_dialog.h"
#include <QCloseEvent>
#include <QSettings>
#include <QDialog>

#include "utils.h"

namespace Ui{
    class loginDialog;
}

class loginDialog : public QDialog{
    Q_OBJECT

public:
    explicit loginDialog(QWidget *parent = 0);
    ~loginDialog();
    void closeEvent(QCloseEvent*);

signals:
    void loginRequested(std::string, std::string);
    void loginDialogClosed();
    void signupRequested();

public slots:
    void accept();
    void reject();
    void on_button_signup_clicked();
    void on_checkbox_remember_password_stateChanged(int);
    void on_loginFailed();

private:
    Ui::loginDialog* ui;
    void WriteSettings();
    void ReadSettings();
};

#endif
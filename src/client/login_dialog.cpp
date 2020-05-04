#include "client/login_dialog.h"

loginDialog::loginDialog(QWidget *parent):
    ui(new Ui::loginDialog)
{
    ui->setupUi(this);
    setWindowTitle(tr("Sign In"));
}

loginDialog::~loginDialog(){
    ;
}

void loginDialog::on_button_signup_clicked(){
    emit signupRequested();
}

void loginDialog::accept(){
    if(!isUsernameOrPasswordValid(ui->line_edit_username->text().toStdString()) 
        || !isUsernameOrPasswordValid(ui->line_edit_password->text().toStdString()))
    {
        QMessageBox::warning(this, tr("Login"),
            tr("Username or password empty!\n"));
    }
    else
    {
        emit loginRequested(ui->line_edit_username->text().toStdString(), 
            ui->line_edit_password->text().toStdString());
    }
}

void loginDialog::reject(){
    close();
}

void loginDialog::on_checkbox_remember_password_stateChanged(int state){
    if(state != 0)  ReadSettings();
}

void loginDialog::on_loginFailed(){
    QMessageBox::warning(this, tr("Login"),
        tr("Invalid username or password!\n"));
    show();
}

void loginDialog::closeEvent(QCloseEvent* event){
    emit loginDialogClosed();
}

void loginDialog::WriteSettings(){
    QSettings settings("Qt_socket_client", "chat");
    settings.setValue("username",ui->line_edit_username->text());
    settings.setValue("password",ui->line_edit_password->text());
}

void loginDialog::ReadSettings(){
    QSettings settings("Qt_socket_client", "chat");
    settings.setValue("username", ui->line_edit_username->text());
    if(ui->checkbox_remember_password->isChecked()){
        settings.setValue("password", ui->line_edit_password->text());
    }
}

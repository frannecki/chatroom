#include "client/register_dialog.h"

registerDialog::registerDialog(QWidget* parent):
    ui(new Ui::registerDialog)
{
    ui->setupUi(this);
    setWindowTitle(tr("Sign Up"));
    ui->label_note->setText("Please note that username and password \nshould not be empty. Spaces are not allowed.");
}

registerDialog::~registerDialog(){
    ;
}

void registerDialog::accept(){
    if(ui->line_edit_password->text() != ui->line_edit_password_2->text()){
        QMessageBox::warning(this, tr("Registration"),
            tr("Password inconsistent!\n"));
        return;
    }
    if(!isUsernameOrPasswordValid(ui->line_edit_username->text().toStdString()) 
        || !isUsernameOrPasswordValid(ui->line_edit_password->text().toStdString()))
    {
        QMessageBox::warning(this, tr("Registration"),
            tr("Username or password empty!\n"));
        return;
    }
    emit registerRequested(ui->line_edit_username->text().toStdString(),
        ui->line_edit_password->text().toStdString());
}

void registerDialog::on_registration_succeeded(){
    QMessageBox::warning(this, tr("Registration"),
            tr("Registration Succeeded\n"));
}

void registerDialog::on_registration_failed(){
    QMessageBox::warning(this, tr("Registration"),
            tr("Registration Failed! Please use another username\n"));
}

void registerDialog::on_signupRequested(){
    show();
}

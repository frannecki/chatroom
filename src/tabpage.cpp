#include "tabpage.h"

TabPage::TabPage(QWidget *parent):
    ui(new Ui::TabPage), 
    QMainWindow(parent)
{
    
}

void TabPage::init(thread_client* _client){
    ui->setupUi(this);
    client_ = _client;
    reset();
}

void TabPage::reset(){
    uname_dest = std::string("default");
    ui->select_widget->setVisible(true);
    ui->chat_widget->setVisible(false);
}

TabPage::~TabPage(){
    delete ui;
}

void TabPage::on_ok_button_clicked(){
    ui->select_widget->setVisible(false);
    ui->chat_widget->setVisible(true);
    uname_dest = ui->combo_box_chat->currentText().toStdString();
    emit contact_selected(idx);
}

void TabPage::on_cancel_button_clicked(){
    emit contact_cancelled(idx);
}

void TabPage::on_send_button_clicked(){
    std::string msg_content = ui->line_edit_msg->text().toStdString();
    if(msg_content.size() == 0)  return;
    std::string mssg = uname_dest + std::string(" ") + msg_content;
    std::string msg = std::string("I: ") + ui->line_edit_msg->text().toStdString();
    client_->sendMsg(mssg);
    client_->updateChatBox(idx, msg);
}

void TabPage::updateChatView(){
    ui->chatBox->scrollToBottom();
}
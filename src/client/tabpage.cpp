#include "client/tabpage.h"

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
    uname_dest = "default";
    ui->chat_widget->setVisible(true);
}

TabPage::~TabPage(){
    delete ui;
}

void TabPage::on_send_button_clicked(){
    std::string msg_content = ui->line_edit_msg->text().toStdString();
    if(msg_content.empty())  return;
    client_->sendMsg(MESSAGE, uname_dest, msg_content);
    std::string msg = std::string("I: ") + ui->line_edit_msg->text().toStdString();
    client_->updateChatBox(idx, msg);
}

void TabPage::updateChatView(){
    ui->chatBox->scrollToBottom();
}

#include "mainwindow_client.h"

MainWindow::MainWindow(int argc, char **argv, QWidget *parent):
    ui(new Ui::MainWindow), 
    QMainWindow(parent), 
    is_client_launched(false)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/images/icon.png"));
    
    QObject::connect(&client_, SIGNAL(msgRecvd(int)), this, SLOT(updateChatView(int)));
    QObject::connect(&client_, SIGNAL(connection_rejected()), this, SLOT(on_connection_rejected()));
    QObject::connect(&client_, SIGNAL(connection_interrupted()), this, SLOT(on_connection_interrupted()));
    QObject::connect(&client_, SIGNAL(logUpdated()), this, SLOT(updateLoggingView()));
    QObject::connect(&client_, SIGNAL(msgFromNew(int)), this, SLOT(on_msg_from_new(int)));
    QObject::connect(&client_, SIGNAL(file_open_error()), this, SLOT(on_file_open_error()));
    if(ui->checkbox_remember_settings->isChecked()){
        ReadSettings();
    }

    ui->list_view_logging->setModel(client_.logModel());
    ui->connect_button->setEnabled(false);
    ui->open_new_button->setEnabled(false);
    ui->close_current_button->setEnabled(false);

    for(int i = 1; i <= MAXCONTACTS; ++i){
        tabpages[i].init(&client_);
        tabpages[i].idx = i;
        QObject::connect(&(tabpages[i]), SIGNAL(contact_selected(int)), this, SLOT(on_contact_selected(int)));
        QObject::connect(&(tabpages[i]), SIGNAL(contact_cancelled(int)), this, SLOT(on_contact_cancelled(int)));
    }
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_checkbox_remember_settings_stateChanged(int state){
    if(state != 0)  ReadSettings();
}

void MainWindow::on_connect_button_clicked(){
    if(!client_.init(ui->line_edit_addr->text().toStdString(), 
                 ui->line_edit_port->text().toStdString()))
    {
        showNoServerMessage();
    }
    else{
        ui->connect_button->setEnabled(false);
        ui->line_edit_addr->setReadOnly(true);
        ui->line_edit_port->setReadOnly(true);
        is_client_launched = true;
    }
}

void MainWindow::on_start_button_clicked(){
    client_.setNickname(ui->combo_box_login->currentText().toStdString());
    ui->start_button->setEnabled(false);
    ui->connect_button->setEnabled(true);
    ui->open_new_button->setEnabled(true);
    ui->close_current_button->setEnabled(true);
    setWindowTitle(tr("Demo Client - ") + ui->combo_box_login->currentText());
}

void MainWindow::on_close_current_button_clicked(){
    int index = ui->tab_manager->currentIndex();
    std::string contname = ui->tab_manager->tabText(index).toStdString();
    
    int cntCont = client_.removeContact(index);
    if(cntCont == -1){
        QMessageBox msgBox;
        msgBox.setText("[ERROR] Cannot remove current contact!");
        msgBox.exec();
        return;
    }

    if(index <= cntCont){
        tabpages[index].ui->chatBox->setModel(client_.chatBox(index));
        tabpages[index].uname_dest = client_.getContName(index);
        ui->tab_manager->setTabText(index, QString::fromStdString(tabpages[index].uname_dest));
    }

    ui->tab_manager->removeTab(cntCont+1);
    tabpages[cntCont+1].reset();
}

void MainWindow::on_open_new_button_clicked(){
    int cntCont = client_.getCntCont();
    if(cntCont >= MAXCONTACTS){
        QMessageBox msgBox;
        msgBox.setText("[ERROR] Excceeded contact limit!");
        msgBox.exec();
    }
    else{
        ui->tab_manager->addTab(&(tabpages[cntCont+1]), QString("New Tab"));
        ui->open_new_button->setEnabled(false);
        ui->close_current_button->setEnabled(false);
    }
}

void MainWindow::updateChatView(int idx){
    tabpages[idx].updateChatView();
}

void MainWindow::updateLoggingView(){
    ui->list_view_logging->scrollToBottom();
}

void MainWindow::on_msg_from_new(int cntCont){
    tabpages[cntCont].uname_dest = client_.getContName(cntCont);
    ui->tab_manager->addTab(&(tabpages[cntCont]), QString::fromStdString(tabpages[cntCont].uname_dest));
    tabpages[cntCont].ui->select_widget->setVisible(false);
    tabpages[cntCont].ui->chat_widget->setVisible(true);
    tabpages[cntCont].ui->chatBox->setModel(client_.chatBox(cntCont));
    ui->open_new_button->setEnabled(true);
    ui->close_current_button->setEnabled(true);
}

void MainWindow::on_contact_cancelled(int idx){
    ui->tab_manager->removeTab(idx);
    ui->open_new_button->setEnabled(true);
    ui->close_current_button->setEnabled(true);
}

void MainWindow::on_contact_selected(int idx){
    //std::string contname = tabpages[idx].uname_dest;
    std::string contname = tabpages[idx].ui->combo_box_chat->currentText().toStdString();
    int cntCont = client_.addContact(contname);
    if(cntCont == -1){
        QMessageBox msgBox;
        msgBox.setText("[ERROR] Contact in communication!");
        msgBox.exec();
        ui->tab_manager->removeTab(idx);
        tabpages[idx].reset();
    }
    else{
        ui->tab_manager->setTabText(cntCont, QString::fromStdString(contname));
        tabpages[cntCont].ui->chatBox->setModel(client_.chatBox(cntCont));
    }
    ui->open_new_button->setEnabled(true);
    ui->close_current_button->setEnabled(true);
}

void MainWindow::on_action_About_triggered(){
    QMessageBox::about(this, tr("About"), 
        tr("<h2>Chatroom Demo App v0.0</h2><p>&#169; 2019 frannecki</p>"));
}

void MainWindow::on_file_open_error(){
    QMessageBox msgBox;
    msgBox.setText("[ERROR] Cannot open file!");
    msgBox.exec();
}

void MainWindow::on_action_Open_triggered(){
    QString filename = QFileDialog::getOpenFileName(this, tr("Select file"), "./");
}

void MainWindow::on_action_Quit_triggered(){
    closeExec();
}

void MainWindow::on_quit_button_clicked(){
    closeExec();
}

void MainWindow::on_connection_rejected(){
    QMessageBox msgBox;
    msgBox.setText("[Error] Connection to server is rejeted! (logged in or limit excceeded.)");
    msgBox.exec();
    closeExec();
}

void MainWindow::on_connection_interrupted(){
    QMessageBox msgBox;
    msgBox.setText("[Error] Connection to server is interrupted!");
    msgBox.exec();
    closeExec();
}

//void MainWindow::on_file_recvd(int contact, std::string fname){}

void MainWindow::showNoServerMessage(){
    QMessageBox msgBox;
    msgBox.setText("[Error] Couldn't connect to server!");
    msgBox.exec();
    closeExec();
}

void MainWindow::ReadSettings(){
    QSettings settings("Qt_socket_client", "chatroom_demo");
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("windowState").toByteArray());
    QString addr_srv = settings.value("addr_srv",QString("127.0.0.1")).toString();
    QString port_srv = settings.value("port_srv", QString("11311")).toString();
    ui->line_edit_addr->setText(addr_srv);
    ui->line_edit_port->setText(port_srv);
}

void MainWindow::WriteSettings(){
    QSettings settings("Qt_socket_client", "chatroom_demo");
    settings.setValue("addr_srv",ui->line_edit_addr->text());
    settings.setValue("port_srv",ui->line_edit_port->text());
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());
}

void MainWindow::closeExec(){
    if(is_client_launched)  client_.closeAll();
    close();
}

void MainWindow::closeEvent(QCloseEvent *event){
    WriteSettings();
    QMainWindow::closeEvent(event);
}
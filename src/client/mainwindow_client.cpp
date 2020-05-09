#include "client/mainwindow_client.h"

MainWindow::MainWindow(int argc, char **argv, QWidget *parent):
    ui(new Ui::MainWindow), 
    QMainWindow(parent), 
    is_client_launched(false),
    tab_manager(new qtabwidget_h),
    list_view_logging(new QListView)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/images/icon.png"));
    ui->search_button->setEnabled(false);

    ipaddr_server = (argc > 1)?std::string(argv[1]):"127.0.0.2";
    port_server = (argc > 2)?std::string(argv[2]):"11311";
    
    QObject::connect(&client_, SIGNAL(msgRecvd(int)), this, SLOT(updateChatView(int)));
    QObject::connect(&client_, SIGNAL(connection_rejected()), this, SLOT(on_connection_rejected()));
    QObject::connect(&client_, SIGNAL(connection_interrupted()), this, SLOT(on_connection_interrupted()));
    QObject::connect(&client_, SIGNAL(logUpdated()), this, SLOT(updateLoggingView()));
    QObject::connect(&client_, SIGNAL(msgFromNew(int)), this, SLOT(on_msg_from_new(int)));
    QObject::connect(&client_, SIGNAL(file_open_error()), this, SLOT(on_file_open_error()));
    QObject::connect(&client_, SIGNAL(connection_established()), this, SLOT(on_connection_established()));
    QObject::connect(&client_, SIGNAL(registration_succeeded()), &register_dialog, SLOT(on_registration_succeeded()));
    QObject::connect(&client_, SIGNAL(registration_failed()), &register_dialog, SLOT(on_registration_failed()));
    QObject::connect(&client_, SIGNAL(login_failed()), &login_dialog, SLOT(on_loginFailed()));
    QObject::connect(&client_, SIGNAL(users_found(const char*)), this, SLOT(on_users_found(const char*)));
    QObject::connect(&client_, SIGNAL(file_recv_finished(const QString&)), this, SLOT(on_file_recv_finished(const QString&)));
    QObject::connect(&login_dialog, SIGNAL(loginRequested(std::string, std::string)), this, SLOT(on_loginRequested(std::string, std::string)));
    QObject::connect(&login_dialog, SIGNAL(loginDialogClosed()), this, SLOT(on_loginDialogClosed()));
    QObject::connect(&login_dialog, SIGNAL(signupRequested()), &register_dialog, SLOT(on_signupRequested()));
    QObject::connect(&register_dialog, SIGNAL(registerRequested(std::string, std::string)), this, SLOT(on_registerRequested(std::string, std::string)));
    QObject::connect(ui->list_contacts, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(on_contactDoubleClicked(QListWidgetItem*)));
    if(ui->checkbox_remember_settings->isChecked()){
        ReadSettings();
    }

    list_view_logging->setModel(client_.logModel());
    
    ui->centralwidget->layout()->addWidget(tab_manager);
    tab_manager->addTab(list_view_logging, QString("logging"));

    for(int i = 1; i <= MAXCONTACTS; ++i){
        tabpages[i].init(&client_);
        tabpages[i].idx = i;
    }

    this->show();
    login_dialog.show();
    register_dialog.hide();
}

MainWindow::~MainWindow(){
    register_dialog.close();
    delete ui;
}

void MainWindow::on_checkbox_remember_settings_stateChanged(int state){
    if(state != 0)  ReadSettings();
}

void MainWindow::updateChatView(int idx){
    tabpages[idx].updateChatView();
}

void MainWindow::updateLoggingView(){
    list_view_logging->scrollToBottom();
}

void MainWindow::on_msg_from_new(int cntCont){
    tabpages[cntCont].uname_dest = client_.getContName(cntCont);
    tab_manager->addTab(&(tabpages[cntCont]), QString::fromStdString(tabpages[cntCont].uname_dest));
    tabpages[cntCont].ui->chatBox->setModel(client_.chatBox(cntCont));
}

void MainWindow::on_contact_cancelled(int idx){
    tab_manager->removeTab(idx);
}

void MainWindow::on_users_found(const char* users){
    char user[15] = {'\0'};
    int len = strlen(users);
    int idx = 0;
    while(idx < len){
        if((idx == 0 || users[idx-1] == ' ') && users[idx] != ' '){
            sscanf(users+idx, "%s", user);
            ui->list_contacts->addItem(new QListWidgetItem(QIcon(":/images/chat.svg"), QString(user)));
        }
        ++idx;
    }
}

void MainWindow::on_loginRequested(std::string username, std::string password){
    client_.setNickname(username);
    client_.setPassword(password);
    setWindowTitle(tr("Demo Client - ") + QString::fromStdString(username));
    if(!client_.init(ipaddr_server, port_server, CLIENT_LOGIN)){
        showNoServerMessage();
    }
    else  ui->search_button->setEnabled(true);
}

void MainWindow::on_registerRequested(std::string username, std::string password){
    client_.setNickname(username);
    client_.setPassword(password);
    if(!client_.init("127.0.0.2", "11311", CLIENT_REGISTER)){
        showNoServerMessage();
    }
}

void MainWindow::on_loginDialogClosed(){
    if(!is_client_launched){
        close();
    }
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
    std::string filename = QFileDialog::getOpenFileName(this, tr("Select file"), "./").toStdString();
    if(filename.empty()){
        return;
    }
    client_.transferFile(filename, tabpages[tab_manager->currentIndex()].uname_dest);
}

void MainWindow::on_file_recv_finished(const QString& fname){
    // get directory to save the file cache in .TEMP_${nickname};
    QString filename = QFileDialog::getSaveFileName(this, tr("Save File"), QString("./") + fname);
    if(filename.isEmpty()){
        return;
    }
    std::string movTmpFile = "mv '.TEMP_" + client_.getNickname() + 
        "/" + fname.toStdString() + "' '" + filename.toStdString() + "'";
    system(movTmpFile.c_str());
}

void MainWindow::on_action_Quit_triggered(){
    closeExec();
}

void MainWindow::on_quit_button_clicked(){
    closeExec();
}

void MainWindow::on_search_button_clicked(){
    ui->list_contacts->clear();
    std::string username = ui->line_edit_search->text().toStdString();
    client_.sendMsg(USER_SEARCH, std::string("server"), username);
}

void MainWindow::on_connection_established(){
    printf("[INFO] MainWindow: Connection Established.\n");
    is_client_launched = true;
    login_dialog.close();
    this->show();
}

void MainWindow::on_connection_rejected(){
    QMessageBox msgBox;
    msgBox.setText("[Error] Connection to server is rejeted! (logged in or limit excceeded.)");
    msgBox.exec();
    client_.closeAll();
    close();
}

void MainWindow::on_connection_interrupted(){
    QMessageBox msgBox;
    msgBox.setText("[Error] Connection to server is interrupted!");
    msgBox.exec();
    closeExec();
}

void MainWindow::on_contactDoubleClicked(QListWidgetItem* item){
    std::string contname = item->text().toStdString();
    int cntCont = client_.addContact(contname);
    if(cntCont == -1){
        QMessageBox msgBox;
        msgBox.setText("[ERROR] Contact in communication or chat limit excceeded!");
        msgBox.exec();
    }
    else{
        tabpages[cntCont].uname_dest = contname;
        tab_manager->addTab(&(tabpages[cntCont]), QString::fromStdString(contname));
        tabpages[cntCont].ui->chatBox->setModel(client_.chatBox(cntCont));
    }
}

void MainWindow::on_close_current_button_clicked(){
    int index = tab_manager->currentIndex();
    std::string contname = tab_manager->tabText(index).toStdString();
    
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
        tab_manager->setTabText(index, QString::fromStdString(tabpages[index].uname_dest));
    }

    tab_manager->removeTab(cntCont+1);
    tabpages[cntCont+1].reset();
}

//void MainWindow::on_file_recvd(int contact, std::string fname){}

void MainWindow::showNoServerMessage(){
    QMessageBox msgBox;
    msgBox.setText("[Error] Couldn't connect to server!");
    msgBox.exec();
    closeExec();
}

void MainWindow::ReadSettings(){
    QSettings settings("Qt_socket_client", "chat");
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("windowState").toByteArray());
}

void MainWindow::WriteSettings(){
    QSettings settings("Qt_socket_client", "chat");
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());
}

void MainWindow::closeExec(){
    client_.closeAll();
    close();
}

void MainWindow::closeEvent(QCloseEvent *event){
    WriteSettings();
    register_dialog.close();
    login_dialog.close();
    QMainWindow::closeEvent(event);
}

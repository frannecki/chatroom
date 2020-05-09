#ifndef MAINWINDOW_CLIENT_H
#define MAINWINDOW_CLIENT_H
#include "ui_mainwindow_client.h"
#include "tabpage.h"
#include "qtabbar_h.h"
#include "login_dialog.h"
#include "register_dialog.h"
#include <QMainWindow>
#include <QCloseEvent>
#include <QSettings>
#include <QMessageBox>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QListView>

#include "thread_client.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(int argc, char **argv, QWidget *parent = 0);
    ~MainWindow();
    void ReadSettings();
    void WriteSettings();
    void closeEvent(QCloseEvent *event);
    void showNoServerMessage();

private slots:
    // by name
    void on_action_About_triggered();
    void on_action_Quit_triggered();
    void on_action_Open_triggered();
    void on_quit_button_clicked();
    void on_search_button_clicked();
    void on_close_current_button_clicked();
    void on_checkbox_remember_settings_stateChanged(int);

    // customized
    void on_connection_established();
    void on_connection_rejected();
    void on_connection_interrupted();
    void updateLoggingView();
    void updateChatView(int);
    void on_msg_from_new(int);
    void on_contact_cancelled(int);
    void on_file_open_error();
    void on_file_recv_finished(const QString&);
    void on_users_found(const char*);
    //void on_file_recvd(int, std::string);
    void on_loginRequested(std::string, std::string);
    void on_loginDialogClosed();
    void on_registerRequested(std::string, std::string);
    void on_contactDoubleClicked(QListWidgetItem*);

private:
    Ui::MainWindow *ui;
    qtabwidget_h* tab_manager;
    loginDialog login_dialog;
    registerDialog register_dialog;
    QListView *list_view_logging;

    thread_client client_;
    bool is_client_launched;
    TabPage tabpages[MAXCONTACTS+1];

    std::string ipaddr_server;
    std::string port_server;
    void closeExec();
};

#endif
#ifndef MAINWINDOW_CLIENT_H
#define MAINWINDOW_CLIENT_H
#include "ui_mainwindow_client.h"
#include "tabpage.h"
#include <QMainWindow>
#include <QCloseEvent>
#include <QSettings>
#include <QMessageBox>
#include <QFileDialog>

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
    void on_connect_button_clicked();
    void on_start_button_clicked();
    void on_close_current_button_clicked();
    void on_open_new_button_clicked();
    void on_action_Quit_triggered();
    void on_action_Open_triggered();
    void on_quit_button_clicked();
    void on_checkbox_remember_settings_stateChanged(int state);

    // customized
    void on_connection_rejected();
    void on_connection_interrupted();
    void updateLoggingView();
    void updateChatView(int);
    void on_msg_from_new(int);
    void on_contact_selected(int);
    void on_contact_cancelled(int);
    void on_file_open_error();
    //void on_file_recvd(int, std::string);

private:
    Ui::MainWindow *ui;
    thread_client client_;
    bool is_client_launched;
    TabPage tabpages[MAXCONTACTS+1];
    void closeExec();
};

#endif
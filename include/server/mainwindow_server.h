#ifndef MAINWINDOW_SERVER_H
#define MAINWINDOW_SERVER_H
#include "ui_mainwindow_server.h"
#include <QMainWindow>
#include <QCloseEvent>
#include <QSettings>
#include <QMessageBox>
#include <QPixmap>
#include <QPalette>

#include "thread_server.h"

namespace Ui {
class MainWindow_;
}

class MainWindow_ : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow_(int argc, char **argv, QWidget *parent = 0);
    ~MainWindow_();
    void ReadSettings();
    void WriteSettings();
    void closeEvent(QCloseEvent *event);
    void showNoServerMessage();

private slots:
    void on_action_About_triggered();
    void on_connect_button_clicked();
    void on_quit_button_clicked();
    void on_action_Quit_triggered();
    void updateLoggingView();
    void on_checkbox_remember_settings_stateChanged(int state);

private:
    Ui::MainWindow_ *ui;
    thread_server server_;
};

#endif // MAINWINDOW_SERVER_H

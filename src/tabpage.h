#ifndef TABPAGE_H
#define TABPAGE_H
#include "ui_tabpage.h"
#include "thread_client.h"
#include <QMainWindow>
#include <QMessageBox>

namespace Ui {
class TabPage;
}

class TabPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit TabPage(QWidget *parent = 0);
    ~TabPage();
    void init(thread_client*);
    void reset();
    void updateChatView();
    Ui::TabPage *ui;
    thread_client* client_;
    std::string uname_dest;
    int idx;

signals:
    void contact_selected(int);
    void contact_cancelled(int);

public slots:
    void on_send_button_clicked();
    void on_ok_button_clicked();
    void on_cancel_button_clicked();
};

#endif
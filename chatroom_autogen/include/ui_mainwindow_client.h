/********************************************************************************
** Form generated from reading UI file 'mainwindow_client.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_CLIENT_H
#define UI_MAINWINDOW_CLIENT_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_Quit;
    QAction *action_Preferences;
    QAction *action_About;
    QAction *action_Open;
    QAction *actionClose;
    QWidget *centralwidget;
    QHBoxLayout *hboxLayout;
    QTabWidget *tab_manager;
    QWidget *tab;
    QGridLayout *gridLayout_3;
    QGroupBox *group_box_logging;
    QGridLayout *gridLayout_6;
    QListView *list_view_logging;
    QMenuBar *menubar;
    QMenu *menu_File;
    QMenu *menuDemo_App;
    QStatusBar *statusbar;
    QDockWidget *dock_status;
    QWidget *dockWidgetContents_2;
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *group_box_user;
    QGridLayout *gridLayout_5;
    QComboBox *combo_box_login;
    QLabel *nickname;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *start_button;
    QGroupBox *group_box_server;
    QGridLayout *gridLayout;
    QLabel *label_ip_port;
    QPushButton *connect_button;
    QSpacerItem *horizontalSpacer;
    QCheckBox *checkbox_remember_settings;
    QLineEdit *line_edit_port;
    QLineEdit *line_edit_addr;
    QLabel *label_ip_addr;
    QGroupBox *group_box_chatorder;
    QGridLayout *gridLayout_2;
    QPushButton *close_current_button;
    QPushButton *open_new_button;
    QSpacerItem *verticalSpacer_3;
    QPushButton *quit_button;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(873, 776);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        action_Quit = new QAction(MainWindow);
        action_Quit->setObjectName(QString::fromUtf8("action_Quit"));
        action_Quit->setShortcutContext(Qt::ApplicationShortcut);
        action_Preferences = new QAction(MainWindow);
        action_Preferences->setObjectName(QString::fromUtf8("action_Preferences"));
        action_About = new QAction(MainWindow);
        action_About->setObjectName(QString::fromUtf8("action_About"));
        action_Open = new QAction(MainWindow);
        action_Open->setObjectName(QString::fromUtf8("action_Open"));
        actionClose = new QAction(MainWindow);
        actionClose->setObjectName(QString::fromUtf8("actionClose"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        hboxLayout = new QHBoxLayout(centralwidget);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        tab_manager = new QTabWidget(centralwidget);
        tab_manager->setObjectName(QString::fromUtf8("tab_manager"));
        tab_manager->setMinimumSize(QSize(100, 0));
        tab_manager->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayout_3 = new QGridLayout(tab);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        group_box_logging = new QGroupBox(tab);
        group_box_logging->setObjectName(QString::fromUtf8("group_box_logging"));
        gridLayout_6 = new QGridLayout(group_box_logging);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        list_view_logging = new QListView(group_box_logging);
        list_view_logging->setObjectName(QString::fromUtf8("list_view_logging"));

        gridLayout_6->addWidget(list_view_logging, 0, 0, 1, 1);


        gridLayout_3->addWidget(group_box_logging, 0, 0, 1, 1);

        tab_manager->addTab(tab, QString());

        hboxLayout->addWidget(tab_manager);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 873, 36));
        menu_File = new QMenu(menubar);
        menu_File->setObjectName(QString::fromUtf8("menu_File"));
        menuDemo_App = new QMenu(menubar);
        menuDemo_App->setObjectName(QString::fromUtf8("menuDemo_App"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        dock_status = new QDockWidget(MainWindow);
        dock_status->setObjectName(QString::fromUtf8("dock_status"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(dock_status->sizePolicy().hasHeightForWidth());
        dock_status->setSizePolicy(sizePolicy);
        dock_status->setMinimumSize(QSize(480, 693));
        dock_status->setAllowedAreas(Qt::RightDockWidgetArea);
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QString::fromUtf8("dockWidgetContents_2"));
        verticalLayout = new QVBoxLayout(dockWidgetContents_2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame = new QFrame(dockWidgetContents_2);
        frame->setObjectName(QString::fromUtf8("frame"));
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(frame);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        group_box_user = new QGroupBox(frame);
        group_box_user->setObjectName(QString::fromUtf8("group_box_user"));
        gridLayout_5 = new QGridLayout(group_box_user);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        combo_box_login = new QComboBox(group_box_user);
        combo_box_login->addItem(QString());
        combo_box_login->addItem(QString());
        combo_box_login->addItem(QString());
        combo_box_login->addItem(QString());
        combo_box_login->addItem(QString());
        combo_box_login->addItem(QString());
        combo_box_login->setObjectName(QString::fromUtf8("combo_box_login"));

        gridLayout_5->addWidget(combo_box_login, 1, 1, 1, 1);

        nickname = new QLabel(group_box_user);
        nickname->setObjectName(QString::fromUtf8("nickname"));
        nickname->setEnabled(true);
        nickname->setFrameShape(QFrame::StyledPanel);
        nickname->setFrameShadow(QFrame::Raised);

        gridLayout_5->addWidget(nickname, 1, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_2, 4, 0, 1, 1);

        start_button = new QPushButton(group_box_user);
        start_button->setObjectName(QString::fromUtf8("start_button"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(start_button->sizePolicy().hasHeightForWidth());
        start_button->setSizePolicy(sizePolicy1);

        gridLayout_5->addWidget(start_button, 4, 1, 1, 1);


        verticalLayout_3->addWidget(group_box_user);

        group_box_server = new QGroupBox(frame);
        group_box_server->setObjectName(QString::fromUtf8("group_box_server"));
        gridLayout = new QGridLayout(group_box_server);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_ip_port = new QLabel(group_box_server);
        label_ip_port->setObjectName(QString::fromUtf8("label_ip_port"));
        label_ip_port->setFrameShape(QFrame::StyledPanel);
        label_ip_port->setFrameShadow(QFrame::Raised);

        gridLayout->addWidget(label_ip_port, 2, 0, 1, 1);

        connect_button = new QPushButton(group_box_server);
        connect_button->setObjectName(QString::fromUtf8("connect_button"));
        connect_button->setEnabled(true);
        sizePolicy1.setHeightForWidth(connect_button->sizePolicy().hasHeightForWidth());
        connect_button->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(connect_button, 5, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(170, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 5, 0, 1, 1);

        checkbox_remember_settings = new QCheckBox(group_box_server);
        checkbox_remember_settings->setObjectName(QString::fromUtf8("checkbox_remember_settings"));
        checkbox_remember_settings->setLayoutDirection(Qt::RightToLeft);

        gridLayout->addWidget(checkbox_remember_settings, 4, 0, 1, 2);

        line_edit_port = new QLineEdit(group_box_server);
        line_edit_port->setObjectName(QString::fromUtf8("line_edit_port"));

        gridLayout->addWidget(line_edit_port, 3, 0, 1, 2);

        line_edit_addr = new QLineEdit(group_box_server);
        line_edit_addr->setObjectName(QString::fromUtf8("line_edit_addr"));

        gridLayout->addWidget(line_edit_addr, 1, 0, 1, 2);

        label_ip_addr = new QLabel(group_box_server);
        label_ip_addr->setObjectName(QString::fromUtf8("label_ip_addr"));
        label_ip_addr->setFrameShape(QFrame::StyledPanel);
        label_ip_addr->setFrameShadow(QFrame::Raised);

        gridLayout->addWidget(label_ip_addr, 0, 0, 1, 1);


        verticalLayout_3->addWidget(group_box_server);

        group_box_chatorder = new QGroupBox(frame);
        group_box_chatorder->setObjectName(QString::fromUtf8("group_box_chatorder"));
        gridLayout_2 = new QGridLayout(group_box_chatorder);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        close_current_button = new QPushButton(group_box_chatorder);
        close_current_button->setObjectName(QString::fromUtf8("close_current_button"));

        gridLayout_2->addWidget(close_current_button, 0, 1, 1, 1);

        open_new_button = new QPushButton(group_box_chatorder);
        open_new_button->setObjectName(QString::fromUtf8("open_new_button"));

        gridLayout_2->addWidget(open_new_button, 0, 0, 1, 1);


        verticalLayout_3->addWidget(group_box_chatorder);

        verticalSpacer_3 = new QSpacerItem(20, 233, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_3);


        verticalLayout->addWidget(frame);

        quit_button = new QPushButton(dockWidgetContents_2);
        quit_button->setObjectName(QString::fromUtf8("quit_button"));
        sizePolicy1.setHeightForWidth(quit_button->sizePolicy().hasHeightForWidth());
        quit_button->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(quit_button);

        dock_status->setWidget(dockWidgetContents_2);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dock_status);

        menubar->addAction(menuDemo_App->menuAction());
        menubar->addAction(menu_File->menuAction());
        menu_File->addSeparator();
        menu_File->addAction(action_About);
        menu_File->addSeparator();
        menuDemo_App->addAction(action_Open);
        menuDemo_App->addAction(action_Quit);

        retranslateUi(MainWindow);

        tab_manager->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Demo Client", nullptr));
        action_Quit->setText(QApplication::translate("MainWindow", "&Quit", nullptr));
#ifndef QT_NO_SHORTCUT
        action_Quit->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", nullptr));
#endif // QT_NO_SHORTCUT
        action_Preferences->setText(QApplication::translate("MainWindow", "&Preferences", nullptr));
        action_About->setText(QApplication::translate("MainWindow", "&About", nullptr));
        action_Open->setText(QApplication::translate("MainWindow", "&Open", nullptr));
#ifndef QT_NO_SHORTCUT
        action_Open->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_NO_SHORTCUT
        actionClose->setText(QApplication::translate("MainWindow", "&Close", nullptr));
        group_box_logging->setTitle(QApplication::translate("MainWindow", "logging", nullptr));
        tab_manager->setTabText(tab_manager->indexOf(tab), QApplication::translate("MainWindow", "view_logging", nullptr));
        menu_File->setTitle(QApplication::translate("MainWindow", "&Help", nullptr));
        menuDemo_App->setTitle(QApplication::translate("MainWindow", "&File", nullptr));
        dock_status->setWindowTitle(QApplication::translate("MainWindow", "Command Panel", nullptr));
        group_box_user->setTitle(QApplication::translate("MainWindow", "User", nullptr));
        combo_box_login->setItemText(0, QApplication::translate("MainWindow", "Johnny", nullptr));
        combo_box_login->setItemText(1, QApplication::translate("MainWindow", "Kimberly", nullptr));
        combo_box_login->setItemText(2, QApplication::translate("MainWindow", "David", nullptr));
        combo_box_login->setItemText(3, QApplication::translate("MainWindow", "Alice", nullptr));
        combo_box_login->setItemText(4, QApplication::translate("MainWindow", "Sally", nullptr));
        combo_box_login->setItemText(5, QApplication::translate("MainWindow", "Wolfgang", nullptr));

        nickname->setText(QApplication::translate("MainWindow", "Nickname", nullptr));
        start_button->setText(QApplication::translate("MainWindow", "Start", nullptr));
        group_box_server->setTitle(QApplication::translate("MainWindow", "Server", nullptr));
        label_ip_port->setText(QApplication::translate("MainWindow", "Port", nullptr));
#ifndef QT_NO_TOOLTIP
        connect_button->setToolTip(QApplication::translate("MainWindow", "Set the target to the current joint trajectory state.", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        connect_button->setStatusTip(QApplication::translate("MainWindow", "Clear all waypoints and set the target to the current joint trajectory state.", nullptr));
#endif // QT_NO_STATUSTIP
        connect_button->setText(QApplication::translate("MainWindow", "Connect", nullptr));
        checkbox_remember_settings->setText(QApplication::translate("MainWindow", "Remember settings on startup", nullptr));
        line_edit_port->setText(QApplication::translate("MainWindow", "11311", nullptr));
        line_edit_addr->setText(QApplication::translate("MainWindow", "127.0.0.2", nullptr));
        label_ip_addr->setText(QApplication::translate("MainWindow", "IP Address", nullptr));
        group_box_chatorder->setTitle(QApplication::translate("MainWindow", "Chat", nullptr));
        close_current_button->setText(QApplication::translate("MainWindow", "Close Tab", nullptr));
        open_new_button->setText(QApplication::translate("MainWindow", "New Tab", nullptr));
        quit_button->setText(QApplication::translate("MainWindow", "Quit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_CLIENT_H

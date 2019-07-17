/********************************************************************************
** Form generated from reading UI file 'mainwindow_server.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_SERVER_H
#define UI_MAINWINDOW_SERVER_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
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

class Ui_MainWindow_
{
public:
    QAction *action_Quit;
    QAction *action_Preferences;
    QAction *action_About;
    QAction *actionOpen;
    QAction *actionClose;
    QWidget *centralwidget;
    QHBoxLayout *hboxLayout;
    QTabWidget *tab_manager;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_6;
    QGroupBox *groupBox_image_2;
    QGridLayout *gridLayout_2;
    QListView *logView;
    QMenuBar *menubar;
    QMenu *menu_File;
    QMenu *menuDemo_App;
    QStatusBar *statusbar;
    QDockWidget *dock_status;
    QWidget *dockWidgetContents_2;
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label_ip_port;
    QPushButton *connect_button;
    QSpacerItem *horizontalSpacer;
    QCheckBox *checkbox_remember_settings;
    QLineEdit *line_edit_port;
    QLineEdit *line_edit_addr;
    QLabel *label_ip_addr;
    QSpacerItem *verticalSpacer_3;
    QPushButton *quit_button;

    void setupUi(QMainWindow *MainWindow_)
    {
        if (MainWindow_->objectName().isEmpty())
            MainWindow_->setObjectName(QString::fromUtf8("MainWindow_"));
        MainWindow_->resize(873, 776);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow_->setWindowIcon(icon);
        MainWindow_->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        action_Quit = new QAction(MainWindow_);
        action_Quit->setObjectName(QString::fromUtf8("action_Quit"));
        action_Quit->setShortcutContext(Qt::ApplicationShortcut);
        action_Preferences = new QAction(MainWindow_);
        action_Preferences->setObjectName(QString::fromUtf8("action_Preferences"));
        action_About = new QAction(MainWindow_);
        action_About->setObjectName(QString::fromUtf8("action_About"));
        actionOpen = new QAction(MainWindow_);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionClose = new QAction(MainWindow_);
        actionClose->setObjectName(QString::fromUtf8("actionClose"));
        centralwidget = new QWidget(MainWindow_);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        hboxLayout = new QHBoxLayout(centralwidget);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        tab_manager = new QTabWidget(centralwidget);
        tab_manager->setObjectName(QString::fromUtf8("tab_manager"));
        tab_manager->setMinimumSize(QSize(100, 0));
        tab_manager->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout_6 = new QVBoxLayout(tab_2);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        groupBox_image_2 = new QGroupBox(tab_2);
        groupBox_image_2->setObjectName(QString::fromUtf8("groupBox_image_2"));
        gridLayout_2 = new QGridLayout(groupBox_image_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        logView = new QListView(groupBox_image_2);
        logView->setObjectName(QString::fromUtf8("logView"));
        logView->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(logView->sizePolicy().hasHeightForWidth());
        logView->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(logView, 4, 0, 3, 2);


        verticalLayout_6->addWidget(groupBox_image_2);

        tab_manager->addTab(tab_2, QString());

        hboxLayout->addWidget(tab_manager);

        MainWindow_->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow_);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 873, 36));
        menu_File = new QMenu(menubar);
        menu_File->setObjectName(QString::fromUtf8("menu_File"));
        menuDemo_App = new QMenu(menubar);
        menuDemo_App->setObjectName(QString::fromUtf8("menuDemo_App"));
        MainWindow_->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow_);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow_->setStatusBar(statusbar);
        dock_status = new QDockWidget(MainWindow_);
        dock_status->setObjectName(QString::fromUtf8("dock_status"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(dock_status->sizePolicy().hasHeightForWidth());
        dock_status->setSizePolicy(sizePolicy1);
        dock_status->setMinimumSize(QSize(480, 680));
        dock_status->setAllowedAreas(Qt::RightDockWidgetArea);
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QString::fromUtf8("dockWidgetContents_2"));
        verticalLayout = new QVBoxLayout(dockWidgetContents_2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame = new QFrame(dockWidgetContents_2);
        frame->setObjectName(QString::fromUtf8("frame"));
        sizePolicy1.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy1);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(frame);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        groupBox = new QGroupBox(frame);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_ip_port = new QLabel(groupBox);
        label_ip_port->setObjectName(QString::fromUtf8("label_ip_port"));
        label_ip_port->setFrameShape(QFrame::StyledPanel);
        label_ip_port->setFrameShadow(QFrame::Raised);

        gridLayout->addWidget(label_ip_port, 2, 0, 1, 1);

        connect_button = new QPushButton(groupBox);
        connect_button->setObjectName(QString::fromUtf8("connect_button"));
        connect_button->setEnabled(true);
        QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(connect_button->sizePolicy().hasHeightForWidth());
        connect_button->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(connect_button, 5, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(170, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 5, 0, 1, 1);

        checkbox_remember_settings = new QCheckBox(groupBox);
        checkbox_remember_settings->setObjectName(QString::fromUtf8("checkbox_remember_settings"));
        checkbox_remember_settings->setLayoutDirection(Qt::RightToLeft);

        gridLayout->addWidget(checkbox_remember_settings, 4, 0, 1, 2);

        line_edit_port = new QLineEdit(groupBox);
        line_edit_port->setObjectName(QString::fromUtf8("line_edit_port"));

        gridLayout->addWidget(line_edit_port, 3, 0, 1, 2);

        line_edit_addr = new QLineEdit(groupBox);
        line_edit_addr->setObjectName(QString::fromUtf8("line_edit_addr"));

        gridLayout->addWidget(line_edit_addr, 1, 0, 1, 2);

        label_ip_addr = new QLabel(groupBox);
        label_ip_addr->setObjectName(QString::fromUtf8("label_ip_addr"));
        label_ip_addr->setFrameShape(QFrame::StyledPanel);
        label_ip_addr->setFrameShadow(QFrame::Raised);

        gridLayout->addWidget(label_ip_addr, 0, 0, 1, 1);


        verticalLayout_3->addWidget(groupBox);

        verticalSpacer_3 = new QSpacerItem(20, 233, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_3);


        verticalLayout->addWidget(frame);

        quit_button = new QPushButton(dockWidgetContents_2);
        quit_button->setObjectName(QString::fromUtf8("quit_button"));
        sizePolicy2.setHeightForWidth(quit_button->sizePolicy().hasHeightForWidth());
        quit_button->setSizePolicy(sizePolicy2);

        verticalLayout->addWidget(quit_button);

        dock_status->setWidget(dockWidgetContents_2);
        MainWindow_->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dock_status);

        menubar->addAction(menuDemo_App->menuAction());
        menubar->addAction(menu_File->menuAction());
        menu_File->addAction(action_Preferences);
        menu_File->addSeparator();
        menu_File->addAction(action_About);
        menu_File->addSeparator();
        menuDemo_App->addAction(actionOpen);
        menuDemo_App->addAction(action_Quit);

        retranslateUi(MainWindow_);

        tab_manager->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow_);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow_)
    {
        MainWindow_->setWindowTitle(QApplication::translate("MainWindow_", "Demo Server", nullptr));
        action_Quit->setText(QApplication::translate("MainWindow_", "&Quit", nullptr));
#ifndef QT_NO_SHORTCUT
        action_Quit->setShortcut(QApplication::translate("MainWindow_", "Ctrl+Q", nullptr));
#endif // QT_NO_SHORTCUT
        action_Preferences->setText(QApplication::translate("MainWindow_", "&Preferences", nullptr));
        action_About->setText(QApplication::translate("MainWindow_", "&About", nullptr));
        actionOpen->setText(QApplication::translate("MainWindow_", "&Open", nullptr));
        actionClose->setText(QApplication::translate("MainWindow_", "&Close", nullptr));
        groupBox_image_2->setTitle(QApplication::translate("MainWindow_", "logging", nullptr));
        tab_manager->setTabText(tab_manager->indexOf(tab_2), QApplication::translate("MainWindow_", "view_logging", nullptr));
        menu_File->setTitle(QApplication::translate("MainWindow_", "&Help", nullptr));
        menuDemo_App->setTitle(QApplication::translate("MainWindow_", "&File", nullptr));
        dock_status->setWindowTitle(QApplication::translate("MainWindow_", "Command Panel", nullptr));
        groupBox->setTitle(QApplication::translate("MainWindow_", "Server", nullptr));
        label_ip_port->setText(QApplication::translate("MainWindow_", "Port", nullptr));
#ifndef QT_NO_TOOLTIP
        connect_button->setToolTip(QApplication::translate("MainWindow_", "Set the target to the current joint trajectory state.", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        connect_button->setStatusTip(QApplication::translate("MainWindow_", "Clear all waypoints and set the target to the current joint trajectory state.", nullptr));
#endif // QT_NO_STATUSTIP
        connect_button->setText(QApplication::translate("MainWindow_", "Connect", nullptr));
        checkbox_remember_settings->setText(QApplication::translate("MainWindow_", "Remember settings on startup", nullptr));
        line_edit_port->setText(QApplication::translate("MainWindow_", "11311", nullptr));
        line_edit_addr->setText(QApplication::translate("MainWindow_", "127.0.0.2", nullptr));
        label_ip_addr->setText(QApplication::translate("MainWindow_", "IP Address", nullptr));
        quit_button->setText(QApplication::translate("MainWindow_", "Quit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow_: public Ui_MainWindow_ {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_SERVER_H

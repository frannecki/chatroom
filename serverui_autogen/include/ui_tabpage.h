/********************************************************************************
** Form generated from reading UI file 'tabpage.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TABPAGE_H
#define UI_TABPAGE_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TabPage
{
public:
    QAction *action_Quit;
    QAction *action_Preferences;
    QAction *action_About;
    QAction *actionOpen;
    QAction *actionClose;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QWidget *widget;
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox_chat;
    QGridLayout *gridLayout_2;
    QWidget *select_widget;
    QGridLayout *gridLayout_4;
    QComboBox *combo_box_chat;
    QPushButton *ok_button;
    QLabel *label;
    QPushButton *cancel_button;
    QSpacerItem *verticalSpacer;
    QWidget *chat_widget;
    QGridLayout *gridLayout_5;
    QSpacerItem *horizontalSpacer;
    QPushButton *send_button;
    QListView *chatBox;
    QLineEdit *line_edit_msg;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *TabPage)
    {
        if (TabPage->objectName().isEmpty())
            TabPage->setObjectName(QString::fromUtf8("TabPage"));
        TabPage->resize(681, 706);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        TabPage->setWindowIcon(icon);
        TabPage->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        action_Quit = new QAction(TabPage);
        action_Quit->setObjectName(QString::fromUtf8("action_Quit"));
        action_Quit->setShortcutContext(Qt::ApplicationShortcut);
        action_Preferences = new QAction(TabPage);
        action_Preferences->setObjectName(QString::fromUtf8("action_Preferences"));
        action_About = new QAction(TabPage);
        action_About->setObjectName(QString::fromUtf8("action_About"));
        actionOpen = new QAction(TabPage);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionClose = new QAction(TabPage);
        actionClose->setObjectName(QString::fromUtf8("actionClose"));
        centralwidget = new QWidget(TabPage);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        gridLayout_3 = new QGridLayout(widget);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        groupBox_chat = new QGroupBox(widget);
        groupBox_chat->setObjectName(QString::fromUtf8("groupBox_chat"));
        gridLayout_2 = new QGridLayout(groupBox_chat);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        select_widget = new QWidget(groupBox_chat);
        select_widget->setObjectName(QString::fromUtf8("select_widget"));
        gridLayout_4 = new QGridLayout(select_widget);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        combo_box_chat = new QComboBox(select_widget);
        combo_box_chat->addItem(QString());
        combo_box_chat->addItem(QString());
        combo_box_chat->addItem(QString());
        combo_box_chat->addItem(QString());
        combo_box_chat->addItem(QString());
        combo_box_chat->addItem(QString());
        combo_box_chat->setObjectName(QString::fromUtf8("combo_box_chat"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(combo_box_chat->sizePolicy().hasHeightForWidth());
        combo_box_chat->setSizePolicy(sizePolicy);

        gridLayout_4->addWidget(combo_box_chat, 1, 0, 1, 1);

        ok_button = new QPushButton(select_widget);
        ok_button->setObjectName(QString::fromUtf8("ok_button"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(ok_button->sizePolicy().hasHeightForWidth());
        ok_button->setSizePolicy(sizePolicy1);

        gridLayout_4->addWidget(ok_button, 1, 1, 1, 1);

        label = new QLabel(select_widget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_4->addWidget(label, 0, 0, 1, 2);

        cancel_button = new QPushButton(select_widget);
        cancel_button->setObjectName(QString::fromUtf8("cancel_button"));

        gridLayout_4->addWidget(cancel_button, 1, 2, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer, 2, 0, 1, 3);


        gridLayout_2->addWidget(select_widget, 1, 0, 1, 2);

        chat_widget = new QWidget(groupBox_chat);
        chat_widget->setObjectName(QString::fromUtf8("chat_widget"));
        gridLayout_5 = new QGridLayout(chat_widget);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer, 3, 0, 1, 1);

        send_button = new QPushButton(chat_widget);
        send_button->setObjectName(QString::fromUtf8("send_button"));
        QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(send_button->sizePolicy().hasHeightForWidth());
        send_button->setSizePolicy(sizePolicy2);

        gridLayout_5->addWidget(send_button, 3, 2, 1, 1);

        chatBox = new QListView(chat_widget);
        chatBox->setObjectName(QString::fromUtf8("chatBox"));

        gridLayout_5->addWidget(chatBox, 0, 0, 2, 3);

        line_edit_msg = new QLineEdit(chat_widget);
        line_edit_msg->setObjectName(QString::fromUtf8("line_edit_msg"));

        gridLayout_5->addWidget(line_edit_msg, 2, 0, 1, 3);


        gridLayout_2->addWidget(chat_widget, 2, 0, 1, 2);


        gridLayout_3->addWidget(groupBox_chat, 0, 0, 1, 1);


        gridLayout->addWidget(widget, 0, 0, 1, 1);

        TabPage->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(TabPage);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        TabPage->setStatusBar(statusbar);

        retranslateUi(TabPage);

        QMetaObject::connectSlotsByName(TabPage);
    } // setupUi

    void retranslateUi(QMainWindow *TabPage)
    {
        TabPage->setWindowTitle(QApplication::translate("TabPage", "DemoApp", nullptr));
        action_Quit->setText(QApplication::translate("TabPage", "&Quit", nullptr));
#ifndef QT_NO_SHORTCUT
        action_Quit->setShortcut(QApplication::translate("TabPage", "Ctrl+Q", nullptr));
#endif // QT_NO_SHORTCUT
        action_Preferences->setText(QApplication::translate("TabPage", "&Preferences", nullptr));
        action_About->setText(QApplication::translate("TabPage", "&About", nullptr));
        actionOpen->setText(QApplication::translate("TabPage", "&Open", nullptr));
        actionClose->setText(QApplication::translate("TabPage", "&Close", nullptr));
        groupBox_chat->setTitle(QApplication::translate("TabPage", "Chat", nullptr));
        combo_box_chat->setItemText(0, QApplication::translate("TabPage", "Johnny", nullptr));
        combo_box_chat->setItemText(1, QApplication::translate("TabPage", "Kimberly", nullptr));
        combo_box_chat->setItemText(2, QApplication::translate("TabPage", "David", nullptr));
        combo_box_chat->setItemText(3, QApplication::translate("TabPage", "Alice", nullptr));
        combo_box_chat->setItemText(4, QApplication::translate("TabPage", "Sally", nullptr));
        combo_box_chat->setItemText(5, QApplication::translate("TabPage", "Wolfgang", nullptr));

        ok_button->setText(QApplication::translate("TabPage", "OK", nullptr));
        label->setText(QApplication::translate("TabPage", "Choose whoever you'd like to chat with:", nullptr));
        cancel_button->setText(QApplication::translate("TabPage", "Cancel", nullptr));
        send_button->setText(QApplication::translate("TabPage", "Send", nullptr));
#ifndef QT_NO_SHORTCUT
        send_button->setShortcut(QApplication::translate("TabPage", "Ctrl+Return", nullptr));
#endif // QT_NO_SHORTCUT
    } // retranslateUi

};

namespace Ui {
    class TabPage: public Ui_TabPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TABPAGE_H

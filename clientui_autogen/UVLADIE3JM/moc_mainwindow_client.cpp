/****************************************************************************
** Meta object code from reading C++ file 'mainwindow_client.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/mainwindow_client.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow_client.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[20];
    char stringdata0[427];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 25), // "on_action_About_triggered"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 25), // "on_connect_button_clicked"
QT_MOC_LITERAL(4, 64, 23), // "on_start_button_clicked"
QT_MOC_LITERAL(5, 88, 31), // "on_close_current_button_clicked"
QT_MOC_LITERAL(6, 120, 26), // "on_open_new_button_clicked"
QT_MOC_LITERAL(7, 147, 24), // "on_action_Quit_triggered"
QT_MOC_LITERAL(8, 172, 24), // "on_action_Open_triggered"
QT_MOC_LITERAL(9, 197, 22), // "on_quit_button_clicked"
QT_MOC_LITERAL(10, 220, 42), // "on_checkbox_remember_settings..."
QT_MOC_LITERAL(11, 263, 5), // "state"
QT_MOC_LITERAL(12, 269, 22), // "on_connection_rejected"
QT_MOC_LITERAL(13, 292, 25), // "on_connection_interrupted"
QT_MOC_LITERAL(14, 318, 17), // "updateLoggingView"
QT_MOC_LITERAL(15, 336, 14), // "updateChatView"
QT_MOC_LITERAL(16, 351, 15), // "on_msg_from_new"
QT_MOC_LITERAL(17, 367, 19), // "on_contact_selected"
QT_MOC_LITERAL(18, 387, 20), // "on_contact_cancelled"
QT_MOC_LITERAL(19, 408, 18) // "on_file_open_error"

    },
    "MainWindow\0on_action_About_triggered\0"
    "\0on_connect_button_clicked\0"
    "on_start_button_clicked\0"
    "on_close_current_button_clicked\0"
    "on_open_new_button_clicked\0"
    "on_action_Quit_triggered\0"
    "on_action_Open_triggered\0"
    "on_quit_button_clicked\0"
    "on_checkbox_remember_settings_stateChanged\0"
    "state\0on_connection_rejected\0"
    "on_connection_interrupted\0updateLoggingView\0"
    "updateChatView\0on_msg_from_new\0"
    "on_contact_selected\0on_contact_cancelled\0"
    "on_file_open_error"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   99,    2, 0x08 /* Private */,
       3,    0,  100,    2, 0x08 /* Private */,
       4,    0,  101,    2, 0x08 /* Private */,
       5,    0,  102,    2, 0x08 /* Private */,
       6,    0,  103,    2, 0x08 /* Private */,
       7,    0,  104,    2, 0x08 /* Private */,
       8,    0,  105,    2, 0x08 /* Private */,
       9,    0,  106,    2, 0x08 /* Private */,
      10,    1,  107,    2, 0x08 /* Private */,
      12,    0,  110,    2, 0x08 /* Private */,
      13,    0,  111,    2, 0x08 /* Private */,
      14,    0,  112,    2, 0x08 /* Private */,
      15,    1,  113,    2, 0x08 /* Private */,
      16,    1,  116,    2, 0x08 /* Private */,
      17,    1,  119,    2, 0x08 /* Private */,
      18,    1,  122,    2, 0x08 /* Private */,
      19,    0,  125,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_action_About_triggered(); break;
        case 1: _t->on_connect_button_clicked(); break;
        case 2: _t->on_start_button_clicked(); break;
        case 3: _t->on_close_current_button_clicked(); break;
        case 4: _t->on_open_new_button_clicked(); break;
        case 5: _t->on_action_Quit_triggered(); break;
        case 6: _t->on_action_Open_triggered(); break;
        case 7: _t->on_quit_button_clicked(); break;
        case 8: _t->on_checkbox_remember_settings_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->on_connection_rejected(); break;
        case 10: _t->on_connection_interrupted(); break;
        case 11: _t->updateLoggingView(); break;
        case 12: _t->updateChatView((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->on_msg_from_new((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->on_contact_selected((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->on_contact_cancelled((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->on_file_open_error(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

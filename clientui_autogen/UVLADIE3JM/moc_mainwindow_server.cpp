/****************************************************************************
** Meta object code from reading C++ file 'mainwindow_server.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/mainwindow_server.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow_server.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow__t {
    QByteArrayData data[9];
    char stringdata0[180];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow__t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow__t qt_meta_stringdata_MainWindow_ = {
    {
QT_MOC_LITERAL(0, 0, 11), // "MainWindow_"
QT_MOC_LITERAL(1, 12, 25), // "on_action_About_triggered"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 25), // "on_connect_button_clicked"
QT_MOC_LITERAL(4, 65, 22), // "on_quit_button_clicked"
QT_MOC_LITERAL(5, 88, 24), // "on_action_Quit_triggered"
QT_MOC_LITERAL(6, 113, 17), // "updateLoggingView"
QT_MOC_LITERAL(7, 131, 42), // "on_checkbox_remember_settings..."
QT_MOC_LITERAL(8, 174, 5) // "state"

    },
    "MainWindow_\0on_action_About_triggered\0"
    "\0on_connect_button_clicked\0"
    "on_quit_button_clicked\0on_action_Quit_triggered\0"
    "updateLoggingView\0"
    "on_checkbox_remember_settings_stateChanged\0"
    "state"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow_[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x08 /* Private */,
       3,    0,   45,    2, 0x08 /* Private */,
       4,    0,   46,    2, 0x08 /* Private */,
       5,    0,   47,    2, 0x08 /* Private */,
       6,    0,   48,    2, 0x08 /* Private */,
       7,    1,   49,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,

       0        // eod
};

void MainWindow_::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow_ *_t = static_cast<MainWindow_ *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_action_About_triggered(); break;
        case 1: _t->on_connect_button_clicked(); break;
        case 2: _t->on_quit_button_clicked(); break;
        case 3: _t->on_action_Quit_triggered(); break;
        case 4: _t->updateLoggingView(); break;
        case 5: _t->on_checkbox_remember_settings_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow_::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_MainWindow_.data,
    qt_meta_data_MainWindow_,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow_::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow_::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow_.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow_::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

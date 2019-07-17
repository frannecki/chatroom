/****************************************************************************
** Meta object code from reading C++ file 'tabpage.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/tabpage.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tabpage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TabPage_t {
    QByteArrayData data[7];
    char stringdata0[113];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TabPage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TabPage_t qt_meta_stringdata_TabPage = {
    {
QT_MOC_LITERAL(0, 0, 7), // "TabPage"
QT_MOC_LITERAL(1, 8, 16), // "contact_selected"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 17), // "contact_cancelled"
QT_MOC_LITERAL(4, 44, 22), // "on_send_button_clicked"
QT_MOC_LITERAL(5, 67, 20), // "on_ok_button_clicked"
QT_MOC_LITERAL(6, 88, 24) // "on_cancel_button_clicked"

    },
    "TabPage\0contact_selected\0\0contact_cancelled\0"
    "on_send_button_clicked\0on_ok_button_clicked\0"
    "on_cancel_button_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TabPage[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       3,    1,   42,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   45,    2, 0x0a /* Public */,
       5,    0,   46,    2, 0x0a /* Public */,
       6,    0,   47,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void TabPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TabPage *_t = static_cast<TabPage *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->contact_selected((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->contact_cancelled((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_send_button_clicked(); break;
        case 3: _t->on_ok_button_clicked(); break;
        case 4: _t->on_cancel_button_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TabPage::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TabPage::contact_selected)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (TabPage::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TabPage::contact_cancelled)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject TabPage::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_TabPage.data,
    qt_meta_data_TabPage,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TabPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TabPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TabPage.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int TabPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void TabPage::contact_selected(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TabPage::contact_cancelled(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

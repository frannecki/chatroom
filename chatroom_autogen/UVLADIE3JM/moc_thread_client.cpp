/****************************************************************************
** Meta object code from reading C++ file 'thread_client.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/thread_client.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'thread_client.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_thread_client_t {
    QByteArrayData data[10];
    char stringdata0[127];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_thread_client_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_thread_client_t qt_meta_stringdata_thread_client = {
    {
QT_MOC_LITERAL(0, 0, 13), // "thread_client"
QT_MOC_LITERAL(1, 14, 8), // "msgRecvd"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 9), // "fileRecvd"
QT_MOC_LITERAL(4, 34, 11), // "std::string"
QT_MOC_LITERAL(5, 46, 10), // "logUpdated"
QT_MOC_LITERAL(6, 57, 10), // "msgFromNew"
QT_MOC_LITERAL(7, 68, 19), // "connection_rejected"
QT_MOC_LITERAL(8, 88, 22), // "connection_interrupted"
QT_MOC_LITERAL(9, 111, 15) // "file_open_error"

    },
    "thread_client\0msgRecvd\0\0fileRecvd\0"
    "std::string\0logUpdated\0msgFromNew\0"
    "connection_rejected\0connection_interrupted\0"
    "file_open_error"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_thread_client[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       3,    2,   52,    2, 0x06 /* Public */,
       5,    0,   57,    2, 0x06 /* Public */,
       6,    1,   58,    2, 0x06 /* Public */,
       7,    0,   61,    2, 0x06 /* Public */,
       8,    0,   62,    2, 0x06 /* Public */,
       9,    0,   63,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4,    2,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void thread_client::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        thread_client *_t = static_cast<thread_client *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->msgRecvd((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->fileRecvd((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< std::string(*)>(_a[2]))); break;
        case 2: _t->logUpdated(); break;
        case 3: _t->msgFromNew((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->connection_rejected(); break;
        case 5: _t->connection_interrupted(); break;
        case 6: _t->file_open_error(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (thread_client::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&thread_client::msgRecvd)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (thread_client::*)(int , std::string );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&thread_client::fileRecvd)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (thread_client::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&thread_client::logUpdated)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (thread_client::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&thread_client::msgFromNew)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (thread_client::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&thread_client::connection_rejected)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (thread_client::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&thread_client::connection_interrupted)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (thread_client::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&thread_client::file_open_error)) {
                *result = 6;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject thread_client::staticMetaObject = { {
    &QThread::staticMetaObject,
    qt_meta_stringdata_thread_client.data,
    qt_meta_data_thread_client,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *thread_client::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *thread_client::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_thread_client.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int thread_client::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void thread_client::msgRecvd(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void thread_client::fileRecvd(int _t1, std::string _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void thread_client::logUpdated()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void thread_client::msgFromNew(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void thread_client::connection_rejected()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void thread_client::connection_interrupted()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void thread_client::file_open_error()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

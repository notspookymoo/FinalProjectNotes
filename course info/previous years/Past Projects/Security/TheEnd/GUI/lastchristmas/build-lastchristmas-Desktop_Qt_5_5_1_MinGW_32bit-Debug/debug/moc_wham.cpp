/****************************************************************************
** Meta object code from reading C++ file 'wham.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../lastchristmas/wham.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wham.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_wham_t {
    QByteArrayData data[9];
    char stringdata0[79];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_wham_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_wham_t qt_meta_stringdata_wham = {
    {
QT_MOC_LITERAL(0, 0, 4), // "wham"
QT_MOC_LITERAL(1, 5, 10), // "serConnect"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 13), // "serDisconnect"
QT_MOC_LITERAL(4, 31, 17), // "enumerateSerPorts"
QT_MOC_LITERAL(5, 49, 10), // "populateUI"
QT_MOC_LITERAL(6, 60, 8), // "saveFile"
QT_MOC_LITERAL(7, 69, 4), // "sync"
QT_MOC_LITERAL(8, 74, 4) // "scan"

    },
    "wham\0serConnect\0\0serDisconnect\0"
    "enumerateSerPorts\0populateUI\0saveFile\0"
    "sync\0scan"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_wham[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x0a /* Public */,
       3,    0,   50,    2, 0x0a /* Public */,
       4,    0,   51,    2, 0x0a /* Public */,
       5,    1,   52,    2, 0x0a /* Public */,
       6,    0,   55,    2, 0x0a /* Public */,
       7,    0,   56,    2, 0x0a /* Public */,
       8,    0,   57,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void wham::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        wham *_t = static_cast<wham *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->serConnect(); break;
        case 1: _t->serDisconnect(); break;
        case 2: _t->enumerateSerPorts(); break;
        case 3: _t->populateUI((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->saveFile(); break;
        case 5: _t->sync(); break;
        case 6: _t->scan(); break;
        default: ;
        }
    }
}

const QMetaObject wham::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_wham.data,
      qt_meta_data_wham,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *wham::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *wham::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_wham.stringdata0))
        return static_cast<void*>(const_cast< wham*>(this));
    return QWidget::qt_metacast(_clname);
}

int wham::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE

/****************************************************************************
** Meta object code from reading C++ file 'RetrievalConfig.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../RetrievalConfig.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RetrievalConfig.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_RetrievalConfig_t {
    QByteArrayData data[12];
    char stringdata0[169];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RetrievalConfig_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RetrievalConfig_t qt_meta_stringdata_RetrievalConfig = {
    {
QT_MOC_LITERAL(0, 0, 15), // "RetrievalConfig"
QT_MOC_LITERAL(1, 16, 21), // "onSpinboxValueChanged"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 16), // "onLibPathChanged"
QT_MOC_LITERAL(4, 56, 16), // "onBinPathChanged"
QT_MOC_LITERAL(5, 73, 16), // "onRawPathChanged"
QT_MOC_LITERAL(6, 90, 12), // "selectLibDir"
QT_MOC_LITERAL(7, 103, 13), // "selectBinFile"
QT_MOC_LITERAL(8, 117, 20), // "selectRawFeatureFile"
QT_MOC_LITERAL(9, 138, 7), // "onBtnOk"
QT_MOC_LITERAL(10, 146, 11), // "onBtnCancel"
QT_MOC_LITERAL(11, 158, 10) // "onBtnReset"

    },
    "RetrievalConfig\0onSpinboxValueChanged\0"
    "\0onLibPathChanged\0onBinPathChanged\0"
    "onRawPathChanged\0selectLibDir\0"
    "selectBinFile\0selectRawFeatureFile\0"
    "onBtnOk\0onBtnCancel\0onBtnReset"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RetrievalConfig[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x08 /* Private */,
       3,    0,   67,    2, 0x08 /* Private */,
       4,    0,   68,    2, 0x08 /* Private */,
       5,    0,   69,    2, 0x08 /* Private */,
       6,    0,   70,    2, 0x08 /* Private */,
       7,    0,   71,    2, 0x08 /* Private */,
       8,    0,   72,    2, 0x08 /* Private */,
       9,    0,   73,    2, 0x08 /* Private */,
      10,    0,   74,    2, 0x08 /* Private */,
      11,    0,   75,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void RetrievalConfig::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RetrievalConfig *_t = static_cast<RetrievalConfig *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onSpinboxValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->onLibPathChanged(); break;
        case 2: _t->onBinPathChanged(); break;
        case 3: _t->onRawPathChanged(); break;
        case 4: _t->selectLibDir(); break;
        case 5: _t->selectBinFile(); break;
        case 6: _t->selectRawFeatureFile(); break;
        case 7: _t->onBtnOk(); break;
        case 8: _t->onBtnCancel(); break;
        case 9: _t->onBtnReset(); break;
        default: ;
        }
    }
}

const QMetaObject RetrievalConfig::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_RetrievalConfig.data,
      qt_meta_data_RetrievalConfig,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *RetrievalConfig::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RetrievalConfig::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_RetrievalConfig.stringdata0))
        return static_cast<void*>(const_cast< RetrievalConfig*>(this));
    return QWidget::qt_metacast(_clname);
}

int RetrievalConfig::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

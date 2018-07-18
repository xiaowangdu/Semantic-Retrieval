/****************************************************************************
** Meta object code from reading C++ file 'LMDBGenerator.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../LMDBGenerator.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LMDBGenerator.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_LMDBGenerator_t {
    QByteArrayData data[13];
    char stringdata0[197];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LMDBGenerator_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LMDBGenerator_t qt_meta_stringdata_LMDBGenerator = {
    {
QT_MOC_LITERAL(0, 0, 13), // "LMDBGenerator"
QT_MOC_LITERAL(1, 14, 13), // "selectToolDir"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 13), // "selectRootDir"
QT_MOC_LITERAL(4, 43, 18), // "selectListFilePath"
QT_MOC_LITERAL(5, 62, 18), // "selectOutputDBPath"
QT_MOC_LITERAL(6, 81, 17), // "onToolPathChanged"
QT_MOC_LITERAL(7, 99, 17), // "onRootPathChanged"
QT_MOC_LITERAL(8, 117, 17), // "onListFileChanged"
QT_MOC_LITERAL(9, 135, 21), // "onOutputDBPathChanged"
QT_MOC_LITERAL(10, 157, 11), // "startMakeDB"
QT_MOC_LITERAL(11, 169, 9), // "setDbName"
QT_MOC_LITERAL(12, 179, 17) // "onProcessFinished"

    },
    "LMDBGenerator\0selectToolDir\0\0selectRootDir\0"
    "selectListFilePath\0selectOutputDBPath\0"
    "onToolPathChanged\0onRootPathChanged\0"
    "onListFileChanged\0onOutputDBPathChanged\0"
    "startMakeDB\0setDbName\0onProcessFinished"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LMDBGenerator[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x08 /* Private */,
       3,    0,   70,    2, 0x08 /* Private */,
       4,    0,   71,    2, 0x08 /* Private */,
       5,    0,   72,    2, 0x08 /* Private */,
       6,    0,   73,    2, 0x08 /* Private */,
       7,    0,   74,    2, 0x08 /* Private */,
       8,    0,   75,    2, 0x08 /* Private */,
       9,    0,   76,    2, 0x08 /* Private */,
      10,    0,   77,    2, 0x08 /* Private */,
      11,    0,   78,    2, 0x08 /* Private */,
      12,    1,   79,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void LMDBGenerator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        LMDBGenerator *_t = static_cast<LMDBGenerator *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->selectToolDir(); break;
        case 1: _t->selectRootDir(); break;
        case 2: _t->selectListFilePath(); break;
        case 3: _t->selectOutputDBPath(); break;
        case 4: _t->onToolPathChanged(); break;
        case 5: _t->onRootPathChanged(); break;
        case 6: _t->onListFileChanged(); break;
        case 7: _t->onOutputDBPathChanged(); break;
        case 8: _t->startMakeDB(); break;
        case 9: _t->setDbName(); break;
        case 10: _t->onProcessFinished((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject LMDBGenerator::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_LMDBGenerator.data,
      qt_meta_data_LMDBGenerator,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *LMDBGenerator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LMDBGenerator::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_LMDBGenerator.stringdata0))
        return static_cast<void*>(const_cast< LMDBGenerator*>(this));
    return QWidget::qt_metacast(_clname);
}

int LMDBGenerator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

/****************************************************************************
** Meta object code from reading C++ file 'RetrievalTest.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../RetrievalTest.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RetrievalTest.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_RetrievalTest_t {
    QByteArrayData data[13];
    char stringdata0[183];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RetrievalTest_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RetrievalTest_t qt_meta_stringdata_RetrievalTest = {
    {
QT_MOC_LITERAL(0, 0, 13), // "RetrievalTest"
QT_MOC_LITERAL(1, 14, 11), // "onBtnConfig"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 14), // "selectImageDir"
QT_MOC_LITERAL(4, 42, 17), // "showOriginalImage"
QT_MOC_LITERAL(5, 60, 21), // "checkDownloadFinished"
QT_MOC_LITERAL(6, 82, 18), // "onDownloadComplete"
QT_MOC_LITERAL(7, 101, 15), // "progressChanged"
QT_MOC_LITERAL(8, 117, 21), // "onCanvasDoubleClicked"
QT_MOC_LITERAL(9, 139, 8), // "filename"
QT_MOC_LITERAL(10, 148, 16), // "onStartRetrieval"
QT_MOC_LITERAL(11, 165, 11), // "zoomRequest"
QT_MOC_LITERAL(12, 177, 5) // "delta"

    },
    "RetrievalTest\0onBtnConfig\0\0selectImageDir\0"
    "showOriginalImage\0checkDownloadFinished\0"
    "onDownloadComplete\0progressChanged\0"
    "onCanvasDoubleClicked\0filename\0"
    "onStartRetrieval\0zoomRequest\0delta"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RetrievalTest[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x0a /* Public */,
       3,    0,   60,    2, 0x0a /* Public */,
       4,    0,   61,    2, 0x0a /* Public */,
       5,    0,   62,    2, 0x0a /* Public */,
       6,    1,   63,    2, 0x0a /* Public */,
       7,    2,   66,    2, 0x0a /* Public */,
       8,    1,   71,    2, 0x0a /* Public */,
      10,    0,   74,    2, 0x0a /* Public */,
      11,    1,   75,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,    2,    2,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   12,

       0        // eod
};

void RetrievalTest::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RetrievalTest *_t = static_cast<RetrievalTest *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onBtnConfig(); break;
        case 1: _t->selectImageDir(); break;
        case 2: _t->showOriginalImage(); break;
        case 3: _t->checkDownloadFinished(); break;
        case 4: _t->onDownloadComplete((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->progressChanged((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 6: _t->onCanvasDoubleClicked((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->onStartRetrieval(); break;
        case 8: _t->zoomRequest((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject RetrievalTest::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_RetrievalTest.data,
      qt_meta_data_RetrievalTest,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *RetrievalTest::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RetrievalTest::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_RetrievalTest.stringdata0))
        return static_cast<void*>(const_cast< RetrievalTest*>(this));
    return QWidget::qt_metacast(_clname);
}

int RetrievalTest::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

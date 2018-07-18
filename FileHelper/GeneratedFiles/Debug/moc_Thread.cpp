/****************************************************************************
** Meta object code from reading C++ file 'Thread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Thread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Thread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PasteThread_t {
    QByteArrayData data[7];
    char stringdata0[87];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PasteThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PasteThread_t qt_meta_stringdata_PasteThread = {
    {
QT_MOC_LITERAL(0, 0, 11), // "PasteThread"
QT_MOC_LITERAL(1, 12, 15), // "processProgress"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 2), // "id"
QT_MOC_LITERAL(4, 32, 14), // "bytesProcessed"
QT_MOC_LITERAL(5, 47, 10), // "bytesTotal"
QT_MOC_LITERAL(6, 58, 28) // "sendProcessProgressChangeMsg"

    },
    "PasteThread\0processProgress\0\0id\0"
    "bytesProcessed\0bytesTotal\0"
    "sendProcessProgressChangeMsg"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PasteThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    2,   31,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong, QMetaType::LongLong,    3,    4,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,    4,    5,

       0        // eod
};

void PasteThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PasteThread *_t = static_cast<PasteThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->processProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2])),(*reinterpret_cast< qint64(*)>(_a[3]))); break;
        case 1: _t->sendProcessProgressChangeMsg((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (PasteThread::*_t)(qint64 , qint64 , qint64 );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PasteThread::processProgress)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject PasteThread::staticMetaObject = {
    { &MarkedThread::staticMetaObject, qt_meta_stringdata_PasteThread.data,
      qt_meta_data_PasteThread,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PasteThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PasteThread::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PasteThread.stringdata0))
        return static_cast<void*>(const_cast< PasteThread*>(this));
    return MarkedThread::qt_metacast(_clname);
}

int PasteThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = MarkedThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void PasteThread::processProgress(qint64 _t1, qint64 _t2, qint64 _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_CutPasteThread_t {
    QByteArrayData data[6];
    char stringdata0[84];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CutPasteThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CutPasteThread_t qt_meta_stringdata_CutPasteThread = {
    {
QT_MOC_LITERAL(0, 0, 14), // "CutPasteThread"
QT_MOC_LITERAL(1, 15, 21), // "requestClearClipboard"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 23), // "onGlobalClipboardChange"
QT_MOC_LITERAL(4, 62, 16), // "QClipboard::Mode"
QT_MOC_LITERAL(5, 79, 4) // "mode"

    },
    "CutPasteThread\0requestClearClipboard\0"
    "\0onGlobalClipboardChange\0QClipboard::Mode\0"
    "mode"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CutPasteThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   25,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 4,    5,

       0        // eod
};

void CutPasteThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CutPasteThread *_t = static_cast<CutPasteThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->requestClearClipboard(); break;
        case 1: _t->onGlobalClipboardChange((*reinterpret_cast< QClipboard::Mode(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CutPasteThread::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CutPasteThread::requestClearClipboard)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject CutPasteThread::staticMetaObject = {
    { &PasteThread::staticMetaObject, qt_meta_stringdata_CutPasteThread.data,
      qt_meta_data_CutPasteThread,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CutPasteThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CutPasteThread::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CutPasteThread.stringdata0))
        return static_cast<void*>(const_cast< CutPasteThread*>(this));
    return PasteThread::qt_metacast(_clname);
}

int CutPasteThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PasteThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void CutPasteThread::requestClearClipboard()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
struct qt_meta_stringdata_DeleteThread_t {
    QByteArrayData data[7];
    char stringdata0[71];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DeleteThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DeleteThread_t qt_meta_stringdata_DeleteThread = {
    {
QT_MOC_LITERAL(0, 0, 12), // "DeleteThread"
QT_MOC_LITERAL(1, 13, 14), // "deleteProgress"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 2), // "id"
QT_MOC_LITERAL(4, 32, 16), // "currrentFileName"
QT_MOC_LITERAL(5, 49, 10), // "bytesLeave"
QT_MOC_LITERAL(6, 60, 10) // "totalBytes"

    },
    "DeleteThread\0deleteProgress\0\0id\0"
    "currrentFileName\0bytesLeave\0totalBytes"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DeleteThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    4,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::LongLong, QMetaType::QString, QMetaType::LongLong, QMetaType::LongLong,    3,    4,    5,    6,

       0        // eod
};

void DeleteThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DeleteThread *_t = static_cast<DeleteThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->deleteProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< qint64(*)>(_a[3])),(*reinterpret_cast< qint64(*)>(_a[4]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (DeleteThread::*_t)(qint64 , const QString & , qint64 , qint64 );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DeleteThread::deleteProgress)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject DeleteThread::staticMetaObject = {
    { &MarkedThread::staticMetaObject, qt_meta_stringdata_DeleteThread.data,
      qt_meta_data_DeleteThread,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *DeleteThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DeleteThread::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_DeleteThread.stringdata0))
        return static_cast<void*>(const_cast< DeleteThread*>(this));
    return MarkedThread::qt_metacast(_clname);
}

int DeleteThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = MarkedThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void DeleteThread::deleteProgress(qint64 _t1, const QString & _t2, qint64 _t3, qint64 _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE

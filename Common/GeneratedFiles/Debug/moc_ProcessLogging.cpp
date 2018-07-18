/****************************************************************************
** Meta object code from reading C++ file 'ProcessLogging.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ProcessLogging.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ProcessLogging.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ProcessLogging_t {
    QByteArrayData data[1];
    char stringdata0[15];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ProcessLogging_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ProcessLogging_t qt_meta_stringdata_ProcessLogging = {
    {
QT_MOC_LITERAL(0, 0, 14) // "ProcessLogging"

    },
    "ProcessLogging"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ProcessLogging[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void ProcessLogging::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject ProcessLogging::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ProcessLogging.data,
      qt_meta_data_ProcessLogging,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ProcessLogging::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ProcessLogging::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ProcessLogging.stringdata0))
        return static_cast<void*>(const_cast< ProcessLogging*>(this));
    return QObject::qt_metacast(_clname);
}

int ProcessLogging::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_ConsoleLogging_t {
    QByteArrayData data[1];
    char stringdata0[15];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ConsoleLogging_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ConsoleLogging_t qt_meta_stringdata_ConsoleLogging = {
    {
QT_MOC_LITERAL(0, 0, 14) // "ConsoleLogging"

    },
    "ConsoleLogging"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ConsoleLogging[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void ConsoleLogging::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject ConsoleLogging::staticMetaObject = {
    { &ProcessLogging::staticMetaObject, qt_meta_stringdata_ConsoleLogging.data,
      qt_meta_data_ConsoleLogging,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ConsoleLogging::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ConsoleLogging::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ConsoleLogging.stringdata0))
        return static_cast<void*>(const_cast< ConsoleLogging*>(this));
    return ProcessLogging::qt_metacast(_clname);
}

int ConsoleLogging::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ProcessLogging::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_FileLogging_t {
    QByteArrayData data[1];
    char stringdata0[12];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FileLogging_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FileLogging_t qt_meta_stringdata_FileLogging = {
    {
QT_MOC_LITERAL(0, 0, 11) // "FileLogging"

    },
    "FileLogging"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FileLogging[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void FileLogging::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject FileLogging::staticMetaObject = {
    { &ProcessLogging::staticMetaObject, qt_meta_stringdata_FileLogging.data,
      qt_meta_data_FileLogging,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *FileLogging::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FileLogging::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_FileLogging.stringdata0))
        return static_cast<void*>(const_cast< FileLogging*>(this));
    return ProcessLogging::qt_metacast(_clname);
}

int FileLogging::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ProcessLogging::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_TextBrowserLogging_t {
    QByteArrayData data[1];
    char stringdata0[19];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TextBrowserLogging_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TextBrowserLogging_t qt_meta_stringdata_TextBrowserLogging = {
    {
QT_MOC_LITERAL(0, 0, 18) // "TextBrowserLogging"

    },
    "TextBrowserLogging"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TextBrowserLogging[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void TextBrowserLogging::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject TextBrowserLogging::staticMetaObject = {
    { &ProcessLogging::staticMetaObject, qt_meta_stringdata_TextBrowserLogging.data,
      qt_meta_data_TextBrowserLogging,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TextBrowserLogging::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TextBrowserLogging::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TextBrowserLogging.stringdata0))
        return static_cast<void*>(const_cast< TextBrowserLogging*>(this));
    return ProcessLogging::qt_metacast(_clname);
}

int TextBrowserLogging::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ProcessLogging::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE

/****************************************************************************
** Meta object code from reading C++ file 'FileBrowser.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../FileBrowser.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FileBrowser.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FileBrowser_t {
    QByteArrayData data[17];
    char stringdata0[172];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FileBrowser_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FileBrowser_t qt_meta_stringdata_FileBrowser = {
    {
QT_MOC_LITERAL(0, 0, 11), // "FileBrowser"
QT_MOC_LITERAL(1, 12, 11), // "newFileView"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 11), // "pathChanged"
QT_MOC_LITERAL(4, 37, 4), // "path"
QT_MOC_LITERAL(5, 42, 14), // "deleteFileView"
QT_MOC_LITERAL(6, 57, 14), // "updateFileInfo"
QT_MOC_LITERAL(7, 72, 9), // "QFileInfo"
QT_MOC_LITERAL(8, 82, 8), // "fileInfo"
QT_MOC_LITERAL(9, 91, 4), // "icon"
QT_MOC_LITERAL(10, 96, 15), // "onDeleteClicked"
QT_MOC_LITERAL(11, 112, 6), // "fileUp"
QT_MOC_LITERAL(12, 119, 8), // "fileHome"
QT_MOC_LITERAL(13, 128, 14), // "changeFilePath"
QT_MOC_LITERAL(14, 143, 8), // "new_path"
QT_MOC_LITERAL(15, 152, 13), // "itemActivated"
QT_MOC_LITERAL(16, 166, 5) // "index"

    },
    "FileBrowser\0newFileView\0\0pathChanged\0"
    "path\0deleteFileView\0updateFileInfo\0"
    "QFileInfo\0fileInfo\0icon\0onDeleteClicked\0"
    "fileUp\0fileHome\0changeFilePath\0new_path\0"
    "itemActivated\0index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FileBrowser[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x06 /* Public */,
       3,    1,   60,    2, 0x06 /* Public */,
       5,    1,   63,    2, 0x06 /* Public */,
       6,    2,   66,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    0,   71,    2, 0x08 /* Private */,
      11,    0,   72,    2, 0x08 /* Private */,
      12,    0,   73,    2, 0x08 /* Private */,
      13,    1,   74,    2, 0x08 /* Private */,
      15,    1,   77,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::LongLong,    2,
    QMetaType::Void, 0x80000000 | 7, QMetaType::QIcon,    8,    9,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   14,
    QMetaType::Void, QMetaType::QModelIndex,   16,

       0        // eod
};

void FileBrowser::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FileBrowser *_t = static_cast<FileBrowser *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->newFileView(); break;
        case 1: _t->pathChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->deleteFileView((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 3: _t->updateFileInfo((*reinterpret_cast< const QFileInfo(*)>(_a[1])),(*reinterpret_cast< const QIcon(*)>(_a[2]))); break;
        case 4: _t->onDeleteClicked(); break;
        case 5: _t->fileUp(); break;
        case 6: _t->fileHome(); break;
        case 7: _t->changeFilePath((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->itemActivated((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (FileBrowser::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FileBrowser::newFileView)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (FileBrowser::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FileBrowser::pathChanged)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (FileBrowser::*_t)(qint64 );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FileBrowser::deleteFileView)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (FileBrowser::*_t)(const QFileInfo & , const QIcon & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FileBrowser::updateFileInfo)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject FileBrowser::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_FileBrowser.data,
      qt_meta_data_FileBrowser,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *FileBrowser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FileBrowser::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_FileBrowser.stringdata0))
        return static_cast<void*>(const_cast< FileBrowser*>(this));
    return QWidget::qt_metacast(_clname);
}

int FileBrowser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void FileBrowser::newFileView()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void FileBrowser::pathChanged(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void FileBrowser::deleteFileView(qint64 _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void FileBrowser::updateFileInfo(const QFileInfo & _t1, const QIcon & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE

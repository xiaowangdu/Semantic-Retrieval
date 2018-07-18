/****************************************************************************
** Meta object code from reading C++ file 'fancytabwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../fancytabwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fancytabwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FancyTabWidget_t {
    QByteArrayData data[11];
    char stringdata0[128];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FancyTabWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FancyTabWidget_t qt_meta_stringdata_FancyTabWidget = {
    {
QT_MOC_LITERAL(0, 0, 14), // "FancyTabWidget"
QT_MOC_LITERAL(1, 15, 11), // "ModeChanged"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 20), // "FancyTabWidget::Mode"
QT_MOC_LITERAL(4, 49, 4), // "mode"
QT_MOC_LITERAL(5, 54, 15), // "setCurrentIndex"
QT_MOC_LITERAL(6, 70, 5), // "index"
QT_MOC_LITERAL(7, 76, 7), // "SetMode"
QT_MOC_LITERAL(8, 84, 4), // "Mode"
QT_MOC_LITERAL(9, 89, 20), // "tabBarUpdateGeometry"
QT_MOC_LITERAL(10, 110, 17) // "currentTabChanged"

    },
    "FancyTabWidget\0ModeChanged\0\0"
    "FancyTabWidget::Mode\0mode\0setCurrentIndex\0"
    "index\0SetMode\0Mode\0tabBarUpdateGeometry\0"
    "currentTabChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FancyTabWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   47,    2, 0x0a /* Public */,
       7,    1,   50,    2, 0x0a /* Public */,
       7,    1,   53,    2, 0x0a /* Public */,
       9,    0,   56,    2, 0x08 /* Private */,
      10,    1,   57,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, 0x80000000 | 8,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void FancyTabWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FancyTabWidget *_t = static_cast<FancyTabWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ModeChanged((*reinterpret_cast< FancyTabWidget::Mode(*)>(_a[1]))); break;
        case 1: _t->setCurrentIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->SetMode((*reinterpret_cast< Mode(*)>(_a[1]))); break;
        case 3: _t->SetMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->tabBarUpdateGeometry(); break;
        case 5: _t->currentTabChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (FancyTabWidget::*_t)(FancyTabWidget::Mode );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FancyTabWidget::ModeChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject FancyTabWidget::staticMetaObject = {
    { &QTabWidget::staticMetaObject, qt_meta_stringdata_FancyTabWidget.data,
      qt_meta_data_FancyTabWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *FancyTabWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FancyTabWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_FancyTabWidget.stringdata0))
        return static_cast<void*>(const_cast< FancyTabWidget*>(this));
    return QTabWidget::qt_metacast(_clname);
}

int FancyTabWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTabWidget::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void FancyTabWidget::ModeChanged(FancyTabWidget::Mode _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE

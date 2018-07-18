/****************************************************************************
** Meta object code from reading C++ file 'Canvas.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Canvas.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Canvas.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Canvas_t {
    QByteArrayData data[10];
    char stringdata0[123];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Canvas_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Canvas_t qt_meta_stringdata_Canvas = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Canvas"
QT_MOC_LITERAL(1, 7, 11), // "zoomRequest"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 13), // "scrollRequest"
QT_MOC_LITERAL(4, 34, 15), // "Qt::Orientation"
QT_MOC_LITERAL(5, 50, 8), // "newShape"
QT_MOC_LITERAL(6, 59, 16), // "selectionChanged"
QT_MOC_LITERAL(7, 76, 10), // "shapeMoved"
QT_MOC_LITERAL(8, 87, 14), // "drawingPolygon"
QT_MOC_LITERAL(9, 102, 20) // "mousePositionChanged"

    },
    "Canvas\0zoomRequest\0\0scrollRequest\0"
    "Qt::Orientation\0newShape\0selectionChanged\0"
    "shapeMoved\0drawingPolygon\0"
    "mousePositionChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Canvas[] = {

 // content:
       7,       // revision
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
       8,    1,   62,    2, 0x06 /* Public */,
       9,    2,   65,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4,    2,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,

       0        // eod
};

void Canvas::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Canvas *_t = static_cast<Canvas *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->zoomRequest((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->scrollRequest((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< Qt::Orientation(*)>(_a[2]))); break;
        case 2: _t->newShape(); break;
        case 3: _t->selectionChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->shapeMoved(); break;
        case 5: _t->drawingPolygon((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->mousePositionChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Canvas::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Canvas::zoomRequest)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Canvas::*_t)(int , Qt::Orientation );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Canvas::scrollRequest)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (Canvas::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Canvas::newShape)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (Canvas::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Canvas::selectionChanged)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (Canvas::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Canvas::shapeMoved)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (Canvas::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Canvas::drawingPolygon)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (Canvas::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Canvas::mousePositionChanged)) {
                *result = 6;
                return;
            }
        }
    }
}

const QMetaObject Canvas::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Canvas.data,
      qt_meta_data_Canvas,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Canvas::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Canvas::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Canvas.stringdata0))
        return static_cast<void*>(const_cast< Canvas*>(this));
    return QWidget::qt_metacast(_clname);
}

int Canvas::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void Canvas::zoomRequest(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Canvas::scrollRequest(int _t1, Qt::Orientation _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Canvas::newShape()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void Canvas::selectionChanged(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Canvas::shapeMoved()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}

// SIGNAL 5
void Canvas::drawingPolygon(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void Canvas::mousePositionChanged(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_END_MOC_NAMESPACE

/****************************************************************************
** Meta object code from reading C++ file 'ProtoFileEditor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ProtoFileEditor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ProtoFileEditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ProtoFileEditor_t {
    QByteArrayData data[9];
    char stringdata0[178];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ProtoFileEditor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ProtoFileEditor_t qt_meta_stringdata_ProtoFileEditor = {
    {
QT_MOC_LITERAL(0, 0, 15), // "ProtoFileEditor"
QT_MOC_LITERAL(1, 16, 20), // "requestHighlightHint"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 43), // "QPair<HighlightPosition,Highl..."
QT_MOC_LITERAL(4, 82, 25), // "updateLineNumberAreaWidth"
QT_MOC_LITERAL(5, 108, 13), // "newBlockCount"
QT_MOC_LITERAL(6, 122, 20), // "highlightCurrentLine"
QT_MOC_LITERAL(7, 143, 20), // "updateLineNumberArea"
QT_MOC_LITERAL(8, 164, 13) // "codeBlockHint"

    },
    "ProtoFileEditor\0requestHighlightHint\0"
    "\0QPair<HighlightPosition,HighlightPosition>&\0"
    "updateLineNumberAreaWidth\0newBlockCount\0"
    "highlightCurrentLine\0updateLineNumberArea\0"
    "codeBlockHint"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ProtoFileEditor[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   42,    2, 0x08 /* Private */,
       6,    0,   45,    2, 0x08 /* Private */,
       7,    2,   46,    2, 0x08 /* Private */,
       8,    0,   51,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QRect, QMetaType::Int,    2,    2,
    QMetaType::Void,

       0        // eod
};

void ProtoFileEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ProtoFileEditor *_t = static_cast<ProtoFileEditor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->requestHighlightHint((*reinterpret_cast< QPair<HighlightPosition,HighlightPosition>(*)>(_a[1]))); break;
        case 1: _t->updateLineNumberAreaWidth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->highlightCurrentLine(); break;
        case 3: _t->updateLineNumberArea((*reinterpret_cast< const QRect(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->codeBlockHint(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ProtoFileEditor::*_t)(QPair<HighlightPosition,HighlightPosition> & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ProtoFileEditor::requestHighlightHint)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject ProtoFileEditor::staticMetaObject = {
    { &QPlainTextEdit::staticMetaObject, qt_meta_stringdata_ProtoFileEditor.data,
      qt_meta_data_ProtoFileEditor,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ProtoFileEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ProtoFileEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ProtoFileEditor.stringdata0))
        return static_cast<void*>(const_cast< ProtoFileEditor*>(this));
    return QPlainTextEdit::qt_metacast(_clname);
}

int ProtoFileEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPlainTextEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void ProtoFileEditor::requestHighlightHint(QPair<HighlightPosition,HighlightPosition> & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE

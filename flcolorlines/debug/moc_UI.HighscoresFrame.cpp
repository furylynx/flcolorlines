/****************************************************************************
** Meta object code from reading C++ file 'UI.HighscoresFrame.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/ui/UI.HighscoresFrame.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'UI.HighscoresFrame.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ui__HighscoresFrame_t {
    QByteArrayData data[5];
    char stringdata[63];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_ui__HighscoresFrame_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_ui__HighscoresFrame_t qt_meta_stringdata_ui__HighscoresFrame = {
    {
QT_MOC_LITERAL(0, 0, 19),
QT_MOC_LITERAL(1, 20, 12),
QT_MOC_LITERAL(2, 33, 0),
QT_MOC_LITERAL(3, 34, 12),
QT_MOC_LITERAL(4, 47, 14)
    },
    "ui::HighscoresFrame\0clickedClose\0\0"
    "clickedClear\0clickedRestore\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__HighscoresFrame[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x08,
       3,    0,   30,    2, 0x08,
       4,    0,   31,    2, 0x08,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ui::HighscoresFrame::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        HighscoresFrame *_t = static_cast<HighscoresFrame *>(_o);
        switch (_id) {
        case 0: _t->clickedClose(); break;
        case 1: _t->clickedClear(); break;
        case 2: _t->clickedRestore(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject ui::HighscoresFrame::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_ui__HighscoresFrame.data,
      qt_meta_data_ui__HighscoresFrame,  qt_static_metacall, 0, 0}
};


const QMetaObject *ui::HighscoresFrame::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::HighscoresFrame::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ui__HighscoresFrame.stringdata))
        return static_cast<void*>(const_cast< HighscoresFrame*>(this));
    return QFrame::qt_metacast(_clname);
}

int ui::HighscoresFrame::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

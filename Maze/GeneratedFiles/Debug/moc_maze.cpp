/****************************************************************************
** Meta object code from reading C++ file 'maze.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../maze.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'maze.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Maze_t {
    QByteArrayData data[9];
    char stringdata0[97];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Maze_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Maze_t qt_meta_stringdata_Maze = {
    {
QT_MOC_LITERAL(0, 0, 4), // "Maze"
QT_MOC_LITERAL(1, 5, 9), // "Read_Maze"
QT_MOC_LITERAL(2, 15, 0), // ""
QT_MOC_LITERAL(3, 16, 14), // "Refrush_Widget"
QT_MOC_LITERAL(4, 31, 13), // "invert_Colors"
QT_MOC_LITERAL(5, 45, 9), // "grayscale"
QT_MOC_LITERAL(6, 55, 18), // "CollisionDetection"
QT_MOC_LITERAL(7, 74, 17), // "Check_Same_X_or_Y"
QT_MOC_LITERAL(8, 92, 4) // "Exit"

    },
    "Maze\0Read_Maze\0\0Refrush_Widget\0"
    "invert_Colors\0grayscale\0CollisionDetection\0"
    "Check_Same_X_or_Y\0Exit"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Maze[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x08 /* Private */,
       3,    0,   50,    2, 0x08 /* Private */,
       4,    0,   51,    2, 0x08 /* Private */,
       5,    0,   52,    2, 0x08 /* Private */,
       6,    2,   53,    2, 0x08 /* Private */,
       7,    6,   58,    2, 0x08 /* Private */,
       8,    0,   71,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Float, QMetaType::Float,    2,    2,
    QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    2,    2,    2,    2,    2,    2,
    QMetaType::Void,

       0        // eod
};

void Maze::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Maze *_t = static_cast<Maze *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Read_Maze(); break;
        case 1: _t->Refrush_Widget(); break;
        case 2: _t->invert_Colors(); break;
        case 3: _t->grayscale(); break;
        case 4: _t->CollisionDetection((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 5: { int _r = _t->Check_Same_X_or_Y((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 6: _t->Exit(); break;
        default: ;
        }
    }
}

const QMetaObject Maze::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Maze.data,
      qt_meta_data_Maze,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Maze::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Maze::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Maze.stringdata0))
        return static_cast<void*>(const_cast< Maze*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Maze::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE

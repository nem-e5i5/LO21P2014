/****************************************************************************
** Meta object code from reading C++ file 'ValidatorDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ValidatorDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ValidatorDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ValidatorDialog_t {
    QByteArrayData data[10];
    char stringdata[100];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_ValidatorDialog_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_ValidatorDialog_t qt_meta_stringdata_ValidatorDialog = {
    {
QT_MOC_LITERAL(0, 0, 15),
QT_MOC_LITERAL(1, 16, 12),
QT_MOC_LITERAL(2, 29, 0),
QT_MOC_LITERAL(3, 30, 12),
QT_MOC_LITERAL(4, 43, 12),
QT_MOC_LITERAL(5, 56, 1),
QT_MOC_LITERAL(6, 58, 6),
QT_MOC_LITERAL(7, 65, 13),
QT_MOC_LITERAL(8, 79, 4),
QT_MOC_LITERAL(9, 84, 14)
    },
    "ValidatorDialog\0AjouterLigne\0\0"
    "RetirerLigne\0ComboChanged\0s\0sender\0"
    "TextFocusLost\0send\0TextFocusLost2\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ValidatorDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x0a,
       3,    0,   55,    2, 0x0a,
       4,    2,   56,    2, 0x0a,
       4,    1,   61,    2, 0x2a,
       7,    1,   64,    2, 0x0a,
       7,    0,   67,    2, 0x2a,
       9,    1,   68,    2, 0x0a,
       9,    0,   71,    2, 0x2a,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QObjectStar,    5,    6,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QObjectStar,    8,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QObjectStar,    8,
    QMetaType::Void,

       0        // eod
};

void ValidatorDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ValidatorDialog *_t = static_cast<ValidatorDialog *>(_o);
        switch (_id) {
        case 0: _t->AjouterLigne(); break;
        case 1: _t->RetirerLigne(); break;
        case 2: _t->ComboChanged((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QObject*(*)>(_a[2]))); break;
        case 3: _t->ComboChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->TextFocusLost((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 5: _t->TextFocusLost(); break;
        case 6: _t->TextFocusLost2((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 7: _t->TextFocusLost2(); break;
        default: ;
        }
    }
}

const QMetaObject ValidatorDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ValidatorDialog.data,
      qt_meta_data_ValidatorDialog,  qt_static_metacall, 0, 0}
};


const QMetaObject *ValidatorDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ValidatorDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ValidatorDialog.stringdata))
        return static_cast<void*>(const_cast< ValidatorDialog*>(this));
    if (!strcmp(_clname, "Ui::Validator_dialog"))
        return static_cast< Ui::Validator_dialog*>(const_cast< ValidatorDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int ValidatorDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

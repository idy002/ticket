/****************************************************************************
** Meta object code from reading C++ file 'querytraindialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../querytraindialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'querytraindialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QueryTrainDialog_t {
    QByteArrayData data[13];
    char stringdata0[296];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QueryTrainDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QueryTrainDialog_t qt_meta_stringdata_QueryTrainDialog = {
    {
QT_MOC_LITERAL(0, 0, 16), // "QueryTrainDialog"
QT_MOC_LITERAL(1, 17, 36), // "on_trainListWidget_itemDouble..."
QT_MOC_LITERAL(2, 54, 0), // ""
QT_MOC_LITERAL(3, 55, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(4, 72, 4), // "item"
QT_MOC_LITERAL(5, 77, 26), // "on_startPushButton_clicked"
QT_MOC_LITERAL(6, 104, 29), // "on_dateListWidget_itemClicked"
QT_MOC_LITERAL(7, 134, 35), // "on_dateListWidget_itemDoubleC..."
QT_MOC_LITERAL(8, 170, 24), // "on_delPushButton_clicked"
QT_MOC_LITERAL(9, 195, 25), // "on_stopPushButton_clicked"
QT_MOC_LITERAL(10, 221, 28), // "on_restroePushButton_clicked"
QT_MOC_LITERAL(11, 250, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(12, 272, 23) // "on_pushButton_2_clicked"

    },
    "QueryTrainDialog\0on_trainListWidget_itemDoubleClicked\0"
    "\0QListWidgetItem*\0item\0"
    "on_startPushButton_clicked\0"
    "on_dateListWidget_itemClicked\0"
    "on_dateListWidget_itemDoubleClicked\0"
    "on_delPushButton_clicked\0"
    "on_stopPushButton_clicked\0"
    "on_restroePushButton_clicked\0"
    "on_pushButton_clicked\0on_pushButton_2_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QueryTrainDialog[] = {

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
       1,    1,   59,    2, 0x08 /* Private */,
       5,    0,   62,    2, 0x08 /* Private */,
       6,    1,   63,    2, 0x08 /* Private */,
       7,    1,   66,    2, 0x08 /* Private */,
       8,    0,   69,    2, 0x08 /* Private */,
       9,    0,   70,    2, 0x08 /* Private */,
      10,    0,   71,    2, 0x08 /* Private */,
      11,    0,   72,    2, 0x08 /* Private */,
      12,    0,   73,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void QueryTrainDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QueryTrainDialog *_t = static_cast<QueryTrainDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_trainListWidget_itemDoubleClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 1: _t->on_startPushButton_clicked(); break;
        case 2: _t->on_dateListWidget_itemClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 3: _t->on_dateListWidget_itemDoubleClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 4: _t->on_delPushButton_clicked(); break;
        case 5: _t->on_stopPushButton_clicked(); break;
        case 6: _t->on_restroePushButton_clicked(); break;
        case 7: _t->on_pushButton_clicked(); break;
        case 8: _t->on_pushButton_2_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject QueryTrainDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QueryTrainDialog.data,
      qt_meta_data_QueryTrainDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *QueryTrainDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QueryTrainDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_QueryTrainDialog.stringdata0))
        return static_cast<void*>(const_cast< QueryTrainDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int QueryTrainDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE

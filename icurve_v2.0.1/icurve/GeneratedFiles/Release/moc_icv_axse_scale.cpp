/****************************************************************************
** Meta object code from reading C++ file 'icv_axse_scale.h'
**
** Created: Tue Jun 28 22:48:51 2016
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../include/icv_axse_scale.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'icv_axse_scale.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_IcvAxseSCaleDialog[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x08,
      29,   19,   19,   19, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_IcvAxseSCaleDialog[] = {
    "IcvAxseSCaleDialog\0\0accept()\0reject()\0"
};

const QMetaObject IcvAxseSCaleDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_IcvAxseSCaleDialog,
      qt_meta_data_IcvAxseSCaleDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &IcvAxseSCaleDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *IcvAxseSCaleDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *IcvAxseSCaleDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_IcvAxseSCaleDialog))
        return static_cast<void*>(const_cast< IcvAxseSCaleDialog*>(this));
    if (!strcmp(_clname, "Ui::AxseScaleDialog"))
        return static_cast< Ui::AxseScaleDialog*>(const_cast< IcvAxseSCaleDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int IcvAxseSCaleDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: accept(); break;
        case 1: reject(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

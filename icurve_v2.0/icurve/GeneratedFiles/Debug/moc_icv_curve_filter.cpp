/****************************************************************************
** Meta object code from reading C++ file 'icv_curve_filter.h'
**
** Created: Tue Jun 14 01:04:50 2016
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../include/icv_curve_filter.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'icv_curve_filter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_IcvCurveFilterDialog[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      22,   21,   21,   21, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_IcvCurveFilterDialog[] = {
    "IcvCurveFilterDialog\0\0setFilterType()\0"
};

const QMetaObject IcvCurveFilterDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_IcvCurveFilterDialog,
      qt_meta_data_IcvCurveFilterDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &IcvCurveFilterDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *IcvCurveFilterDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *IcvCurveFilterDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_IcvCurveFilterDialog))
        return static_cast<void*>(const_cast< IcvCurveFilterDialog*>(this));
    if (!strcmp(_clname, "Ui::IcvCurveFilterDialog"))
        return static_cast< Ui::IcvCurveFilterDialog*>(const_cast< IcvCurveFilterDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int IcvCurveFilterDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setFilterType(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

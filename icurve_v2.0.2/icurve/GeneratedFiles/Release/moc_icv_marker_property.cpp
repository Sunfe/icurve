/****************************************************************************
** Meta object code from reading C++ file 'icv_marker_property.h'
**
** Created: Sun Aug 14 23:52:04 2016
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../include/icv_marker_property.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'icv_marker_property.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_IcvMarkerPropertyDialog[] = {

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
      25,   24,   24,   24, 0x08,
      41,   24,   24,   24, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_IcvMarkerPropertyDialog[] = {
    "IcvMarkerPropertyDialog\0\0setMarkerBush()\0"
    "setMarkerPen()\0"
};

const QMetaObject IcvMarkerPropertyDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_IcvMarkerPropertyDialog,
      qt_meta_data_IcvMarkerPropertyDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &IcvMarkerPropertyDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *IcvMarkerPropertyDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *IcvMarkerPropertyDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_IcvMarkerPropertyDialog))
        return static_cast<void*>(const_cast< IcvMarkerPropertyDialog*>(this));
    if (!strcmp(_clname, "Ui::IcvMarkerProperty"))
        return static_cast< Ui::IcvMarkerProperty*>(const_cast< IcvMarkerPropertyDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int IcvMarkerPropertyDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setMarkerBush(); break;
        case 1: setMarkerPen(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

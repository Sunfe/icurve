/****************************************************************************
** Meta object code from reading C++ file 'icv_curve_property.h'
**
** Created: Thu Jun 30 00:37:07 2016
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../include/icv_curve_property.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'icv_curve_property.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_IcvCurvePropertyDialog[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      24,   23,   23,   23, 0x08,
      33,   23,   23,   23, 0x08,
      51,   42,   23,   23, 0x08,
      70,   42,   23,   23, 0x08,
      89,   23,   23,   23, 0x08,
     105,   42,   23,   23, 0x08,
     125,   23,   23,   23, 0x08,
     141,   23,   23,   23, 0x08,
     156,   42,   23,   23, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_IcvCurvePropertyDialog[] = {
    "IcvCurvePropertyDialog\0\0accept()\0"
    "reject()\0indexSel\0setCurveStyle(int)\0"
    "setCurveWidth(int)\0setCurveColor()\0"
    "setMarkerStyle(int)\0setMarkerBush()\0"
    "setMarkerPen()\0setMarkerSize(int)\0"
};

const QMetaObject IcvCurvePropertyDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_IcvCurvePropertyDialog,
      qt_meta_data_IcvCurvePropertyDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &IcvCurvePropertyDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *IcvCurvePropertyDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *IcvCurvePropertyDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_IcvCurvePropertyDialog))
        return static_cast<void*>(const_cast< IcvCurvePropertyDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int IcvCurvePropertyDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: accept(); break;
        case 1: reject(); break;
        case 2: setCurveStyle((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: setCurveWidth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: setCurveColor(); break;
        case 5: setMarkerStyle((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: setMarkerBush(); break;
        case 7: setMarkerPen(); break;
        case 8: setMarkerSize((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

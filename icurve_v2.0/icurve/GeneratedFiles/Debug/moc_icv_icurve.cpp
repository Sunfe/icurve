/****************************************************************************
** Meta object code from reading C++ file 'icv_icurve.h'
**
** Created: Fri Jun 10 18:44:06 2016
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../include/icv_icurve.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'icv_icurve.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_IcvICurve[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   11,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      46,   10,   10,   10, 0x08,
      57,   10,   10,   10, 0x08,
      66,   10,   10,   10, 0x08,
      78,   10,   10,   10, 0x08,
      94,   10,   10,   10, 0x08,
     110,   10,   10,   10, 0x08,
     126,   10,   10,   10, 0x08,
     143,   10,   10,   10, 0x08,
     157,   10,   10,   10, 0x08,
     171,   10,   10,   10, 0x08,
     183,   10,   10,   10, 0x08,
     198,   10,   10,   10, 0x08,
     212,   10,   10,   10, 0x08,
     227,   10,   10,   10, 0x08,
     242,   10,   10,   10, 0x08,
     257,   10,   10,   10, 0x08,
     275,   10,   10,   10, 0x08,
     302,  290,   10,   10, 0x08,
     331,   11,   10,   10, 0x08,
     362,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_IcvICurve[] = {
    "IcvICurve\0\0progress\0analyDataProgress(qint16)\0"
    "openFile()\0saveAs()\0closePlot()\0"
    "setCurveColor()\0setCurveWidth()\0"
    "setCurveStyle()\0setCurveMarker()\0"
    "expandCurve()\0filterCurve()\0findCurve()\0"
    "showAllCurve()\0insertTitle()\0"
    "insertXLabel()\0insertYLabel()\0"
    "insertLegend()\0insertCurveName()\0"
    "insertFooter()\0itemInfo,on\0"
    "legendChecked(QVariant,bool)\0"
    "updateAnalyProgressBar(qint16)\0"
    "cancelAnalyProgressBar()\0"
};

const QMetaObject IcvICurve::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_IcvICurve,
      qt_meta_data_IcvICurve, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &IcvICurve::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *IcvICurve::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *IcvICurve::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_IcvICurve))
        return static_cast<void*>(const_cast< IcvICurve*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int IcvICurve::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: analyDataProgress((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 1: openFile(); break;
        case 2: saveAs(); break;
        case 3: closePlot(); break;
        case 4: setCurveColor(); break;
        case 5: setCurveWidth(); break;
        case 6: setCurveStyle(); break;
        case 7: setCurveMarker(); break;
        case 8: expandCurve(); break;
        case 9: filterCurve(); break;
        case 10: findCurve(); break;
        case 11: showAllCurve(); break;
        case 12: insertTitle(); break;
        case 13: insertXLabel(); break;
        case 14: insertYLabel(); break;
        case 15: insertLegend(); break;
        case 16: insertCurveName(); break;
        case 17: insertFooter(); break;
        case 18: legendChecked((*reinterpret_cast< const QVariant(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 19: updateAnalyProgressBar((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 20: cancelAnalyProgressBar(); break;
        default: ;
        }
        _id -= 21;
    }
    return _id;
}

// SIGNAL 0
void IcvICurve::analyDataProgress(qint16 _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE

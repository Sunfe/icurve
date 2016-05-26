/****************************************************************************
** Meta object code from reading C++ file 'icv_icurve.h'
**
** Created: Thu May 26 21:19:39 2016
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
static const uint qt_meta_data_icurve[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,    8,    7,    7, 0x05,

 // slots: signature, parameters, type, tag, flags
      43,    7,    7,    7, 0x08,
      54,    8,    7,    7, 0x08,
      85,    7,    7,    7, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_icurve[] = {
    "icurve\0\0progress\0analyDataProgress(qint16)\0"
    "openFile()\0updateAnalyProgressBar(qint16)\0"
    "cancelAnalyProgressBar()\0"
};

const QMetaObject icurve::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_icurve,
      qt_meta_data_icurve, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &icurve::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *icurve::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *icurve::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_icurve))
        return static_cast<void*>(const_cast< icurve*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int icurve::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: analyDataProgress((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 1: openFile(); break;
        case 2: updateAnalyProgressBar((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 3: cancelAnalyProgressBar(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void icurve::analyDataProgress(qint16 _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE

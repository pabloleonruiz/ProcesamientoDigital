/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      53,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      19,   11,   11,   11, 0x08,
      37,   11,   32,   11, 0x08,
      55,   11,   11,   11, 0x08,
      63,   11,   11,   11, 0x08,
      72,   11,   11,   11, 0x08,
      82,   11,   11,   11, 0x08,
      95,   11,   11,   11, 0x08,
     109,   11,   11,   11, 0x08,
     120,   11,   11,   11, 0x08,
     128,   11,   11,   11, 0x08,
     140,   11,   11,   11, 0x08,
     153,   11,   11,   11, 0x08,
     163,   11,   11,   11, 0x08,
     177,   11,   11,   11, 0x08,
     182,   11,   11,   11, 0x08,
     189,   11,   11,   11, 0x08,
     199,   11,   11,   11, 0x08,
     212,   11,   11,   11, 0x08,
     223,   11,   11,   11, 0x08,
     231,   11,   11,   11, 0x08,
     240,   11,   11,   11, 0x08,
     253,   11,   11,   11, 0x08,
     266,   11,   11,   11, 0x08,
     273,   11,   11,   11, 0x08,
     281,   11,   11,   11, 0x08,
     292,   11,   11,   11, 0x08,
     306,   11,   11,   11, 0x08,
     314,   11,   11,   11, 0x08,
     325,   11,   11,   11, 0x08,
     332,   11,   11,   11, 0x08,
     342,   11,   11,   11, 0x08,
     350,   11,   11,   11, 0x08,
     361,   11,   11,   11, 0x08,
     368,   11,   11,   11, 0x08,
     378,   11,   11,   11, 0x08,
     385,   11,   11,   11, 0x08,
     395,   11,   11,   11, 0x08,
     408,   11,   11,   11, 0x08,
     416,   11,   11,   11, 0x08,
     425,   11,   11,   11, 0x08,
     435,   11,   11,   11, 0x08,
     446,   11,   11,   11, 0x08,
     457,   11,   11,   11, 0x08,
     468,   11,   11,   11, 0x08,
     484,   11,   11,   11, 0x08,
     494,   11,   11,   11, 0x08,
     508,   11,   11,   11, 0x08,
     518,   11,   11,   11, 0x08,
     531,   11,   11,   11, 0x08,
     544,   11,   11,   11, 0x08,
     559,   11,   11,   11, 0x08,
     573,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0open()\0openRecent()\0bool\0"
    "loadFile(QString)\0print()\0zoomIn()\0"
    "zoomOut()\0normalSize()\0fitToWindow()\0"
    "contents()\0about()\0histogram()\0"
    "normalizar()\0leecock()\0scharcanski()\0"
    "dv()\0dvhd()\0mvdagre()\0mvdcentral()\0"
    "shiozaki()\0pieti()\0manual()\0porcentual()\0"
    "histeresis()\0otsu()\0rosin()\0rosinNor()\0"
    "rosinNorAcu()\0proxi()\0proxiAcu()\0"
    "dist()\0distAcu()\0menor()\0menorAcu()\0"
    "adap()\0adapAcu()\0semi()\0semiAcu()\0"
    "lineargray()\0slide()\0shrink()\0stretch()\0"
    "adaptive()\0colorMap()\0highpass()\0"
    "highFrequency()\0moravec()\0homomorphic()\0"
    "unsharp()\0sharpening()\0meanFilter()\0"
    "medianFilter()\0gaussFilter()\0kuwahara()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->open(); break;
        case 1: _t->openRecent(); break;
        case 2: { bool _r = _t->loadFile((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 3: _t->print(); break;
        case 4: _t->zoomIn(); break;
        case 5: _t->zoomOut(); break;
        case 6: _t->normalSize(); break;
        case 7: _t->fitToWindow(); break;
        case 8: _t->contents(); break;
        case 9: _t->about(); break;
        case 10: _t->histogram(); break;
        case 11: _t->normalizar(); break;
        case 12: _t->leecock(); break;
        case 13: _t->scharcanski(); break;
        case 14: _t->dv(); break;
        case 15: _t->dvhd(); break;
        case 16: _t->mvdagre(); break;
        case 17: _t->mvdcentral(); break;
        case 18: _t->shiozaki(); break;
        case 19: _t->pieti(); break;
        case 20: _t->manual(); break;
        case 21: _t->porcentual(); break;
        case 22: _t->histeresis(); break;
        case 23: _t->otsu(); break;
        case 24: _t->rosin(); break;
        case 25: _t->rosinNor(); break;
        case 26: _t->rosinNorAcu(); break;
        case 27: _t->proxi(); break;
        case 28: _t->proxiAcu(); break;
        case 29: _t->dist(); break;
        case 30: _t->distAcu(); break;
        case 31: _t->menor(); break;
        case 32: _t->menorAcu(); break;
        case 33: _t->adap(); break;
        case 34: _t->adapAcu(); break;
        case 35: _t->semi(); break;
        case 36: _t->semiAcu(); break;
        case 37: _t->lineargray(); break;
        case 38: _t->slide(); break;
        case 39: _t->shrink(); break;
        case 40: _t->stretch(); break;
        case 41: _t->adaptive(); break;
        case 42: _t->colorMap(); break;
        case 43: _t->highpass(); break;
        case 44: _t->highFrequency(); break;
        case 45: _t->moravec(); break;
        case 46: _t->homomorphic(); break;
        case 47: _t->unsharp(); break;
        case 48: _t->sharpening(); break;
        case 49: _t->meanFilter(); break;
        case 50: _t->medianFilter(); break;
        case 51: _t->gaussFilter(); break;
        case 52: _t->kuwahara(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 53)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 53;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

/****************************************************************************
** Meta object code from reading C++ file 'sKDE.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "sKDE.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sKDE.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SimpleUiKde[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x08,
      42,   36,   12,   12, 0x08,
      86,   81,   12,   12, 0x08,
     129,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SimpleUiKde[] = {
    "SimpleUiKde\0\0on_QPushButton_click()\0"
    "index\0on_QComboBox_current_index_change(int)\0"
    "text\0on_QComboBox_current_index_change(QString)\0"
    "on_QRadioButton_toggled(bool)\0"
};

const QMetaObject SimpleUiKde::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SimpleUiKde,
      qt_meta_data_SimpleUiKde, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SimpleUiKde::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SimpleUiKde::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SimpleUiKde::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SimpleUiKde))
        return static_cast<void*>(const_cast< SimpleUiKde*>(this));
    return QWidget::qt_metacast(_clname);
}

int SimpleUiKde::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_QPushButton_click(); break;
        case 1: on_QComboBox_current_index_change((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: on_QComboBox_current_index_change((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: on_QRadioButton_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

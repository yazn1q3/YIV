/****************************************************************************
** Meta object code from reading C++ file 'ImageViewer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../ImageViewer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ImageViewer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ImageViewer_t {
    QByteArrayData data[18];
    char stringdata0[186];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ImageViewer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ImageViewer_t qt_meta_stringdata_ImageViewer = {
    {
QT_MOC_LITERAL(0, 0, 11), // "ImageViewer"
QT_MOC_LITERAL(1, 12, 10), // "openFolder"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 8), // "openFile"
QT_MOC_LITERAL(4, 33, 15), // "addImageFromUrl"
QT_MOC_LITERAL(5, 49, 9), // "showImage"
QT_MOC_LITERAL(6, 59, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(7, 76, 4), // "item"
QT_MOC_LITERAL(8, 81, 6), // "zoomIn"
QT_MOC_LITERAL(9, 88, 7), // "zoomOut"
QT_MOC_LITERAL(10, 96, 14), // "startSlideshow"
QT_MOC_LITERAL(11, 111, 9), // "nextSlide"
QT_MOC_LITERAL(12, 121, 14), // "createPlaylist"
QT_MOC_LITERAL(13, 136, 13), // "addToPlaylist"
QT_MOC_LITERAL(14, 150, 9), // "playVideo"
QT_MOC_LITERAL(15, 160, 4), // "path"
QT_MOC_LITERAL(16, 165, 12), // "searchImages"
QT_MOC_LITERAL(17, 178, 7) // "keyword"

    },
    "ImageViewer\0openFolder\0\0openFile\0"
    "addImageFromUrl\0showImage\0QListWidgetItem*\0"
    "item\0zoomIn\0zoomOut\0startSlideshow\0"
    "nextSlide\0createPlaylist\0addToPlaylist\0"
    "playVideo\0path\0searchImages\0keyword"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ImageViewer[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x08 /* Private */,
       3,    0,   75,    2, 0x08 /* Private */,
       4,    0,   76,    2, 0x08 /* Private */,
       5,    1,   77,    2, 0x08 /* Private */,
       8,    0,   80,    2, 0x08 /* Private */,
       9,    0,   81,    2, 0x08 /* Private */,
      10,    0,   82,    2, 0x08 /* Private */,
      11,    0,   83,    2, 0x08 /* Private */,
      12,    0,   84,    2, 0x08 /* Private */,
      13,    0,   85,    2, 0x08 /* Private */,
      14,    1,   86,    2, 0x08 /* Private */,
      16,    1,   89,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   15,
    QMetaType::Void, QMetaType::QString,   17,

       0        // eod
};

void ImageViewer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ImageViewer *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->openFolder(); break;
        case 1: _t->openFile(); break;
        case 2: _t->addImageFromUrl(); break;
        case 3: _t->showImage((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 4: _t->zoomIn(); break;
        case 5: _t->zoomOut(); break;
        case 6: _t->startSlideshow(); break;
        case 7: _t->nextSlide(); break;
        case 8: _t->createPlaylist(); break;
        case 9: _t->addToPlaylist(); break;
        case 10: _t->playVideo((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 11: _t->searchImages((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ImageViewer::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_ImageViewer.data,
    qt_meta_data_ImageViewer,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ImageViewer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ImageViewer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ImageViewer.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int ImageViewer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

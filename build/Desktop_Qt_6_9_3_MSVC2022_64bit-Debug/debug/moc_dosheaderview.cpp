/****************************************************************************
** Meta object code from reading C++ file 'dosheaderview.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../view/dosheaderview.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dosheaderview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN13DosHeaderViewE_t {};
} // unnamed namespace

template <> constexpr inline auto DosHeaderView::qt_create_metaobjectdata<qt_meta_tag_ZN13DosHeaderViewE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "DosHeaderView",
        "reqModifyDosHeaderValueField",
        "",
        "offset",
        "newValue",
        "reqUpdateData",
        "addData",
        "member",
        "size",
        "value",
        "clearTable",
        "onItemChanged",
        "QStandardItem*",
        "item"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'reqModifyDosHeaderValueField'
        QtMocHelpers::SignalData<void(const QString &, const QString &)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 3 }, { QMetaType::QString, 4 },
        }}),
        // Signal 'reqUpdateData'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'addData'
        QtMocHelpers::SlotData<void(const QString &, const QString &, const QString &, const QString &)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 7 }, { QMetaType::QString, 3 }, { QMetaType::QString, 8 }, { QMetaType::QString, 9 },
        }}),
        // Slot 'clearTable'
        QtMocHelpers::SlotData<void()>(10, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'onItemChanged'
        QtMocHelpers::SlotData<void(QStandardItem *)>(11, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 12, 13 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<DosHeaderView, qt_meta_tag_ZN13DosHeaderViewE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject DosHeaderView::staticMetaObject = { {
    QMetaObject::SuperData::link<QTableView::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13DosHeaderViewE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13DosHeaderViewE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN13DosHeaderViewE_t>.metaTypes,
    nullptr
} };

void DosHeaderView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<DosHeaderView *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->reqModifyDosHeaderValueField((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 1: _t->reqUpdateData(); break;
        case 2: _t->addData((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[4]))); break;
        case 3: _t->clearTable(); break;
        case 4: _t->onItemChanged((*reinterpret_cast< std::add_pointer_t<QStandardItem*>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (DosHeaderView::*)(const QString & , const QString & )>(_a, &DosHeaderView::reqModifyDosHeaderValueField, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (DosHeaderView::*)()>(_a, &DosHeaderView::reqUpdateData, 1))
            return;
    }
}

const QMetaObject *DosHeaderView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DosHeaderView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13DosHeaderViewE_t>.strings))
        return static_cast<void*>(this);
    return QTableView::qt_metacast(_clname);
}

int DosHeaderView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTableView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void DosHeaderView::reqModifyDosHeaderValueField(const QString & _t1, const QString & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1, _t2);
}

// SIGNAL 1
void DosHeaderView::reqUpdateData()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP

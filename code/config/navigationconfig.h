#ifndef NAVIGATIONCONFIG_H
#define NAVIGATIONCONFIG_H

#include <QString>
#include <QList>

#include "enums/navigationitemtypeenum.h"

class  NavigationConfig
{
private:
    NavigationConfig(const QString& name, const QString& icon, NavigationItemTyPeEnum type, NavigationItemTyPeEnum parentType);


    QString name;
    QString icon;
    NavigationItemTyPeEnum type;
    NavigationItemTyPeEnum parentType;


public:
    static const NavigationConfig ITEM_PAGE_DOS_HEADER;
    static const NavigationConfig ITEM_PAGE_NT_HEADERS;
    static const NavigationConfig ITEM_PAGE_FILE_HEADER;
    static const NavigationConfig ITEM_PAGE_OPTIONAL_HEADER;
    static const NavigationConfig ITEM_PAGE_DATA_DIRECTORIES;
    static const NavigationConfig ITEM_PAGE_SECTION_HEADERS;
    static const NavigationConfig ITEM_PAGE_EXPORT_DIRECTORY;
    static const NavigationConfig ITEM_PAGE_IMPORT_DIRECTORY;
    static const NavigationConfig ITEM_PAGE_RESOURCE_DIRECTORY;
    static const NavigationConfig ITEM_PAGE_EXCEPTION_DIRECTORY;
    static const NavigationConfig ITEM_PAGE_RELOCATION_DIRECTORY;
    static const NavigationConfig ITEM_PAGE_DEBUG_DIRECTORY;
    static const NavigationConfig ITEM_PAGE_ADDRESS_CONVERTER;
    static const NavigationConfig ITEM_PAGE_DEPENDENCY_WALKER;
    static const NavigationConfig ITEM_PAGE_HEX_EDITOR;
    static const NavigationConfig ITEM_PAGE_IDENTIFIER;
    static const NavigationConfig ITEM_PAGE_IMPORT_ADDRESS;
    static const NavigationConfig ITEM_PAGE_QUICK_DISASSEMBLER;
    static const NavigationConfig ITEM_PAGE_REBUILDER;
    static const NavigationConfig ITEM_PAGE_RESOURCE_EDITOR;
    static const NavigationConfig ITEM_PAGE_UPX_UTILITY;



    NavigationConfig();
    NavigationConfig(const NavigationConfig& other);


    QString getName() const;
    QString getIcon() const;
    NavigationItemTyPeEnum getType() const;
    NavigationItemTyPeEnum getParentType() const;

    static NavigationConfig of(NavigationItemTyPeEnum type);


    bool equals(NavigationItemTyPeEnum type) const;
    bool equals(const NavigationConfig& other) const;

    NavigationConfig& operator=(const NavigationConfig& other);
    bool operator==(const NavigationConfig& other) const;
    bool operator!=(const NavigationConfig& other) const;

    static QList<NavigationConfig> values();
};

#endif // NAVIGATIONCONFIG_H


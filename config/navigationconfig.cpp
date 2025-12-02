#include "navigationconfig.h"


const NavigationConfig NavigationConfig::ITEM_PAGE_DOS_HEADER("DOS_HEADER", ":/images/images/icon/navigation/m1.ico", PAGE_DOS_HEADER, PAGE_TOP);
const NavigationConfig NavigationConfig::ITEM_PAGE_NT_HEADERS("NT_HEADERS", ":/images/images/icon/navigation/m2.ico", PAGE_NT_HEADERS, PAGE_TOP);
const NavigationConfig NavigationConfig::ITEM_PAGE_FILE_HEADER("FILE_HEADER", ":/images/images/icon/navigation/m3.ico", PAGE_FILE_HEADER, PAGE_NT_HEADERS);
const NavigationConfig NavigationConfig::ITEM_PAGE_OPTIONAL_HEADER("OPTIONAL_HEADER", ":/images/images/icon/navigation/m4.ico", PAGE_OPTIONAL_HEADER, PAGE_NT_HEADERS);
const NavigationConfig NavigationConfig::ITEM_PAGE_DATA_DIRECTORIES("DATA_DIRECTORIES", ":/images/images/icon/navigation/m5.ico", PAGE_DATA_DIRECTORIES, PAGE_OPTIONAL_HEADER);
const NavigationConfig NavigationConfig::ITEM_PAGE_SECTION_HEADERS("SECTION_HEADERS", ":/images/images/icon/navigation/m6.ico", PAGE_SECTION_HEADERS, PAGE_TOP);
const NavigationConfig NavigationConfig::ITEM_PAGE_EXPORT_DIRECTORY("EXPORT_DIRECTORY", ":/images/images/icon/navigation/m7.ico", PAGE_EXPORT_DIRECTORY, PAGE_TOP);
const NavigationConfig NavigationConfig::ITEM_PAGE_IMPORT_DIRECTORY("IMPORT_DIRECTORY", ":/images/images/icon/navigation/m8.ico", PAGE_IMPORT_DIRECTORY, PAGE_TOP);
const NavigationConfig NavigationConfig::ITEM_PAGE_RESOURCE_DIRECTORY("RESOURCE_DIRECTORY", ":/images/images/icon/navigation/m9.ico", PAGE_RESOURCE_DIRECTORY, PAGE_TOP);
const NavigationConfig NavigationConfig::ITEM_PAGE_EXCEPTION_DIRECTORY("EXCEPTION_DIRECTORY", ":/images/images/icon/navigation/m10.ico", PAGE_EXCEPTION_DIRECTORY, PAGE_TOP);
const NavigationConfig NavigationConfig::ITEM_PAGE_RELOCATION_DIRECTORY("RELOCATION_DIRECTORY", ":/images/images/icon/navigation/m8.ico", PAGE_RELOCATION_DIRECTORY, PAGE_TOP);
const NavigationConfig NavigationConfig::ITEM_PAGE_DEBUG_DIRECTORY("DEBUG_DIRECTORY", ":/images/images/icon/navigation/m8.ico", PAGE_DEBUG_DIRECTORY, PAGE_TOP);
const NavigationConfig NavigationConfig::ITEM_PAGE_ADDRESS_CONVERTER("ADDRESS_CONVERTER", ":/images/images/icon/navigation/m8.ico", PAGE_ADDRESS_CONVERTER, PAGE_TOP);
const NavigationConfig NavigationConfig::ITEM_PAGE_DEPENDENCY_WALKER("DEPENDENCY_WALKER", ":/images/images/icon/navigation/m8.ico", PAGE_DEPENDENCY_WALKER, PAGE_TOP);
const NavigationConfig NavigationConfig::ITEM_PAGE_HEX_EDITOR("HEX_EDITOR", ":/images/images/icon/navigation/m8.ico", PAGE_HEX_EDITOR, PAGE_TOP);
const NavigationConfig NavigationConfig::ITEM_PAGE_IDENTIFIER("IDENTIFIER", ":/images/images/icon/navigation/m8.ico", PAGE_IDENTIFIER, PAGE_TOP);
const NavigationConfig NavigationConfig::ITEM_PAGE_IMPORT_ADDRESS("IMPORT_ADDRESS", ":/images/images/icon/navigation/m8.ico", PAGE_IMPORT_ADDRESS, PAGE_TOP);
const NavigationConfig NavigationConfig::ITEM_PAGE_QUICK_DISASSEMBLER("QUICK_DISASSEMBLER", ":/images/images/icon/navigation/m8.ico", PAGE_QUICK_DISASSEMBLER, PAGE_TOP);
const NavigationConfig NavigationConfig::ITEM_PAGE_REBUILDER("REBUILDER", ":/images/images/icon/navigation/m8.ico", PAGE_REBUILDER, PAGE_TOP);
const NavigationConfig NavigationConfig::ITEM_PAGE_RESOURCE_EDITOR("RESOURCE_EDITOR", ":/images/images/icon/navigation/m8.ico", PAGE_RESOURCE_EDITOR, PAGE_TOP);
const NavigationConfig NavigationConfig::ITEM_PAGE_UPX_UTILITY("UPX_UTILITY", ":/images/images/icon/navigation/m8.ico", PAGE_UPX_UTILITY, PAGE_TOP);


NavigationConfig::NavigationConfig(const QString& name, const QString& icon, NavigationItemTyPeEnum type, NavigationItemTyPeEnum parentType) : name(name), icon(icon), type(type), parentType(parentType)
{

}

NavigationConfig::NavigationConfig()
{

}



QList<NavigationConfig> NavigationConfig::values()
{
    QList<NavigationConfig> ret;

    ret.append(ITEM_PAGE_DOS_HEADER);
    ret.append(ITEM_PAGE_NT_HEADERS);
    ret.append(ITEM_PAGE_FILE_HEADER);
    ret.append(ITEM_PAGE_OPTIONAL_HEADER);
    ret.append(ITEM_PAGE_DATA_DIRECTORIES);
    ret.append(ITEM_PAGE_SECTION_HEADERS);
    ret.append(ITEM_PAGE_EXPORT_DIRECTORY);
    ret.append(ITEM_PAGE_IMPORT_DIRECTORY);
    ret.append(ITEM_PAGE_RESOURCE_DIRECTORY);
    ret.append(ITEM_PAGE_EXCEPTION_DIRECTORY);
    ret.append(ITEM_PAGE_RELOCATION_DIRECTORY);
    ret.append(ITEM_PAGE_DEBUG_DIRECTORY);
    ret.append(ITEM_PAGE_ADDRESS_CONVERTER);
    ret.append(ITEM_PAGE_DEPENDENCY_WALKER);
    ret.append(ITEM_PAGE_HEX_EDITOR);
    ret.append(ITEM_PAGE_IDENTIFIER);
    ret.append(ITEM_PAGE_IMPORT_ADDRESS);
    ret.append(ITEM_PAGE_QUICK_DISASSEMBLER);
    ret.append(ITEM_PAGE_REBUILDER);
    ret.append(ITEM_PAGE_RESOURCE_EDITOR);
    ret.append(ITEM_PAGE_UPX_UTILITY);

    return ret;
}

NavigationConfig::NavigationConfig(const NavigationConfig &other) : name(other.name), icon(other.icon), type(other.type),  parentType(other.parentType)
{
}

QString NavigationConfig::getName() const
{
    return name;
}

NavigationItemTyPeEnum NavigationConfig::getType() const
{
    return type;
}

QString NavigationConfig::getIcon() const
{
    return icon;
}

NavigationItemTyPeEnum NavigationConfig::getParentType() const
{
    return parentType;
}

NavigationConfig NavigationConfig::of(NavigationItemTyPeEnum type)
{
    // TODO useless
    return NavigationConfig();
}

bool NavigationConfig::equals(NavigationItemTyPeEnum type) const
{
    return this->type == type;
}

bool NavigationConfig::equals(const NavigationConfig &other) const
{
    return this->type == other.type;
}

NavigationConfig &NavigationConfig::operator=(const NavigationConfig &other)
{
    if (this != &other)
        {
            name = other.getName();
            icon = other.getIcon();
            type = other.getType();
            parentType = other.getParentType();
        }
    return *this;
}

bool NavigationConfig::operator==(const NavigationConfig &other) const
{
    return this->type == other.type;
}

bool NavigationConfig::operator!=(const NavigationConfig &other) const
{
    return this->type != other.type;
}


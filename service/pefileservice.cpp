#include <QFileInfo>

#include "pefileservice.h"
#include "utils/logger.h"

PeFileService::PeFileService()
{
}

PeFileService::~PeFileService()
{
    closePeFile();
}

bool PeFileService::loadPeFile(const QString &filePath)
{
    // 先清理旧的
    closePeFile();

    m_file.setFileName(filePath);
    if (!m_file.open(QIODevice::ReadWrite))
    {
        LOG_ERROR(__FUNCTION__" Failed to open file: %s", filePath.toStdString().c_str());
        return false;
    }

    // 内存映射
    m_data = m_file.map(0, m_file.size());
    if (!m_data)
    {
        LOG_ERROR(__FUNCTION__" Failed to map file to memory.");
        m_file.close();
        return false;
    }

    m_size = m_file.size();


    // 校验 DOS 签名 MZ
    if (m_size < sizeof(IMAGE_DOS_HEADER))
    {
        m_isValid = false;
        return false;
    }

    PIMAGE_DOS_HEADER pDos = reinterpret_cast<PIMAGE_DOS_HEADER>(m_data);

    // 0x5A4D
    if (pDos->e_magic != IMAGE_DOS_SIGNATURE)
    {
        LOG_ERROR(__FUNCTION__" Invalid DOS Signature.");
        m_isValid = false;
        return false;
    }

    m_isValid = true;
    LOG_INFO(__FUNCTION__" PE File loaded successfully: %s", filePath.toStdString().c_str());

    emit reqAfterLoadPeFileSuc(m_file.fileName());

    return true;
}

void PeFileService::closePeFile()
{
    if (m_data && m_file.isOpen())
    {
        m_file.unmap(m_data);
        m_data = nullptr;
    }

    if (m_file.isOpen())
    {
        m_file.close();
        emit reqAfterClosePeFileSuc();
    }

    m_isValid = false;
}

bool PeFileService::isValid() const
{
    return m_isValid;
}

// 解析 DOS Header 并填入通用结构体
QVector<PeFieldData> PeFileService::getDosHeaderData()
{
    QVector<PeFieldData> list;
    if (!m_isValid) return list;

    // 1. 获取 DOS 头指针
    PIMAGE_DOS_HEADER pDos = (PIMAGE_DOS_HEADER)(m_data);

    // 2. 添加一行数据
    // 成员名，成员值的偏移(相对于文件头)，成员大小(sizeof)，成员的值
    auto addRow = [&](const QString& name, DWORD offset, int sizeBytes, quint64 value, const QString& meaning = "")
    {
        PeFieldData data;
        data.member = name;
        // 文件偏移
        data.offset = formatOffset(offset);

        // 大小转为 Word/Dword
        if (sizeBytes == 1) data.size = "Byte";
        else if (sizeBytes == 2) data.size = "Word";
        else if (sizeBytes == 4) data.size = "Dword";
        else data.size = QString::number(sizeBytes);

        // 值转 Hex
        if (sizeBytes == 2) data.value = toHex((WORD)value);
        else if (sizeBytes == 4) data.value = toHex((DWORD)value);
        else data.value = toHex(value);

        data.meaning = meaning;
        list.append(data);
    };

    // 3. 逐个添加 IMAGE_DOS_HEADER 的成员
    addRow("e_magic",    offsetof(IMAGE_DOS_HEADER, e_magic),    2, pDos->e_magic,    "MZ Signature");
    addRow("e_cblp",     offsetof(IMAGE_DOS_HEADER, e_cblp),     2, pDos->e_cblp,     "Bytes on last page of file");
    addRow("e_cp",       offsetof(IMAGE_DOS_HEADER, e_cp),       2, pDos->e_cp,       "Pages in file");
    addRow("e_crlc",     offsetof(IMAGE_DOS_HEADER, e_crlc),     2, pDos->e_crlc,     "Relocations");
    addRow("e_cparhdr",  offsetof(IMAGE_DOS_HEADER, e_cparhdr),  2, pDos->e_cparhdr,  "Size of header in paragraphs");
    addRow("e_minalloc", offsetof(IMAGE_DOS_HEADER, e_minalloc), 2, pDos->e_minalloc, "Minimum extra paragraphs needed");
    addRow("e_maxalloc", offsetof(IMAGE_DOS_HEADER, e_maxalloc), 2, pDos->e_maxalloc, "Maximum extra paragraphs needed");
    addRow("e_ss",       offsetof(IMAGE_DOS_HEADER, e_ss),       2, pDos->e_ss,       "Initial (relative) SS value");
    addRow("e_sp",       offsetof(IMAGE_DOS_HEADER, e_sp),       2, pDos->e_sp,       "Initial SP value");
    addRow("e_csum",     offsetof(IMAGE_DOS_HEADER, e_csum),     2, pDos->e_csum,     "Checksum");
    addRow("e_ip",       offsetof(IMAGE_DOS_HEADER, e_ip),       2, pDos->e_ip,       "Initial IP value");
    addRow("e_cs",       offsetof(IMAGE_DOS_HEADER, e_cs),       2, pDos->e_cs,       "Initial (relative) CS value");
    addRow("e_lfarlc",   offsetof(IMAGE_DOS_HEADER, e_lfarlc),   2, pDos->e_lfarlc,   "File address of relocation table");
    addRow("e_ovno",     offsetof(IMAGE_DOS_HEADER, e_ovno),     2, pDos->e_ovno,     "Overlay number");

    // e_res[4] 保留数组
    addRow("e_res[0]",   offsetof(IMAGE_DOS_HEADER, e_res[0]),   2, pDos->e_res[0],   "Reserved words");
    addRow("e_res[1]",   offsetof(IMAGE_DOS_HEADER, e_res[1]),   2, pDos->e_res[1],   "Reserved words");
    addRow("e_res[2]",   offsetof(IMAGE_DOS_HEADER, e_res[2]),   2, pDos->e_res[2],   "Reserved words");
    addRow("e_res[3]",   offsetof(IMAGE_DOS_HEADER, e_res[3]),   2, pDos->e_res[3],   "Reserved words");


    addRow("e_oemid",    offsetof(IMAGE_DOS_HEADER, e_oemid),    2, pDos->e_oemid,    "OEM identifier (for e_oeminfo)");
    addRow("e_oeminfo",  offsetof(IMAGE_DOS_HEADER, e_oeminfo),  2, pDos->e_oeminfo,  "OEM information; e_oemid specific");

    // e_res2[10]
    addRow("e_res2[0]",  offsetof(IMAGE_DOS_HEADER, e_res2[0]),  2, pDos->e_res2[0],  "Reserved words");
    addRow("e_res2[1]",  offsetof(IMAGE_DOS_HEADER, e_res2[1]),  2, pDos->e_res2[1],  "Reserved words");
    addRow("e_res2[2]",  offsetof(IMAGE_DOS_HEADER, e_res2[2]),  2, pDos->e_res2[2],  "Reserved words");
    addRow("e_res2[3]",  offsetof(IMAGE_DOS_HEADER, e_res2[3]),  2, pDos->e_res2[3],  "Reserved words");
    addRow("e_res2[4]",  offsetof(IMAGE_DOS_HEADER, e_res2[4]),  2, pDos->e_res2[4],  "Reserved words");
    addRow("e_res2[5]",  offsetof(IMAGE_DOS_HEADER, e_res2[5]),  2, pDos->e_res2[5],  "Reserved words");
    addRow("e_res2[6]",  offsetof(IMAGE_DOS_HEADER, e_res2[6]),  2, pDos->e_res2[6],  "Reserved words");
    addRow("e_res2[7]",  offsetof(IMAGE_DOS_HEADER, e_res2[7]),  2, pDos->e_res2[7],  "Reserved words");
    addRow("e_res2[8]",  offsetof(IMAGE_DOS_HEADER, e_res2[8]),  2, pDos->e_res2[8],  "Reserved words");
    addRow("e_res2[9]",  offsetof(IMAGE_DOS_HEADER, e_res2[9]),  2, pDos->e_res2[9],  "Reserved words");

    // 指向 NT 头的偏移
    addRow("e_lfanew",   offsetof(IMAGE_DOS_HEADER, e_lfanew),   4, pDos->e_lfanew,   "Offset to New EXE Header");

    return list;
}

DWORD PeFileService::getNtHeadersOffset() const
{
    if (!m_isValid) return 0;
    PIMAGE_DOS_HEADER pDos = (PIMAGE_DOS_HEADER)(m_data);
    return pDos->e_lfanew;
}

PIMAGE_SECTION_HEADER PeFileService::getSectionHeaderPtr() const
{
    auto pNt = getNtHeaderPtr();
    if (!pNt) return nullptr;
    // 节表紧跟在 Optional Header 后面
    // IMAGE_FIRST_SECTION 宏自动计算位置
    return IMAGE_FIRST_SECTION(pNt);
}

QString PeFileService::formatTimestamp(DWORD timestamp)
{
    return QDateTime::fromSecsSinceEpoch(timestamp).toString("yyyy-MM-dd hh:mm:ss");
}

QVector<PeFieldData> PeFileService::getNtHeaderData()
{
    QVector<PeFieldData> list;
    if (!m_isValid) return list;

    PIMAGE_DOS_HEADER pDos = reinterpret_cast<PIMAGE_DOS_HEADER>(m_data);
    PIMAGE_NT_HEADERS pNt = getNtHeaderPtr();

    // Signature
    DWORD offset = pDos->e_lfanew;

    PeFieldData data;
    data.member = "Signature";
    data.offset = formatOffset(offset);
    data.size = "Dword";
    data.value = toHex(pNt->Signature);
    data.meaning = (pNt->Signature == IMAGE_NT_SIGNATURE) ? "PE Signature" : "Invalid";

    list.append(data);
    return list;
}

QVector<PeFieldData> PeFileService::getFileHeaderData()
{
    QVector<PeFieldData> list;
    if (!m_isValid) return list;

    PIMAGE_DOS_HEADER pDos = reinterpret_cast<PIMAGE_DOS_HEADER>(m_data);
    PIMAGE_FILE_HEADER pFile = getFileHeaderPtr();

    // File Header 开始的偏移 = DOS_e_lfanew + 4 (Signature大小)
    DWORD baseOffset = pDos->e_lfanew + sizeof(DWORD);

    auto add = [&](const QString& name, int relativeOffset, int size, quint64 val, QString meaning = "")
    {
        PeFieldData d;
        d.member = name;
        d.offset = formatOffset(baseOffset + relativeOffset);
        if(size == 1) d.size = "Byte";
        else if(size == 2) d.size = "Word";
        else if(size == 4) d.size = "Dword";
        else d.size = "Qword";

        if (size == 1) d.value = toHex((BYTE)val);
        else if (size == 2) d.value = toHex((WORD)val);
        else if (size == 4) d.value = toHex((DWORD)val);
        else d.value = toHex(val);

        d.meaning = meaning;
        list.append(d);
    };

    add("Machine",              offsetof(IMAGE_FILE_HEADER, Machine),              2, pFile->Machine, "CPU Type");
    add("NumberOfSections",     offsetof(IMAGE_FILE_HEADER, NumberOfSections),     2, pFile->NumberOfSections);
    add("TimeDateStamp",        offsetof(IMAGE_FILE_HEADER, TimeDateStamp),        4, pFile->TimeDateStamp, formatTimestamp(pFile->TimeDateStamp));
    add("PointerToSymbolTable", offsetof(IMAGE_FILE_HEADER, PointerToSymbolTable), 4, pFile->PointerToSymbolTable);
    add("NumberOfSymbols",      offsetof(IMAGE_FILE_HEADER, NumberOfSymbols),      4, pFile->NumberOfSymbols);
    add("SizeOfOptionalHeader", offsetof(IMAGE_FILE_HEADER, SizeOfOptionalHeader), 2, pFile->SizeOfOptionalHeader);
    add("Characteristics",      offsetof(IMAGE_FILE_HEADER, Characteristics),      2, pFile->Characteristics);

    return list;
}

QVector<PeFieldData> PeFileService::getOptionalHeaderData()
{
    QVector<PeFieldData> list;
    if (!m_isValid) return list;

    PIMAGE_DOS_HEADER pDos = reinterpret_cast<PIMAGE_DOS_HEADER>(m_data);
    // OptionalHeader 偏移 = NT头偏移 + 4(Sig) + 20(FileHeader)
    DWORD baseOffset = pDos->e_lfanew + sizeof(DWORD) + sizeof(IMAGE_FILE_HEADER);

    // 先读 Magic 判断位数
    WORD magic = *reinterpret_cast<WORD*>(getOptionalHeaderPtr());

    auto add = [&](const QString& name, int relOffset, int size, quint64 val, QString meaning = "")
    {
        PeFieldData d;
        d.member = name;
        d.offset = formatOffset(baseOffset + relOffset);
        if(size == 1) d.size = "Byte";
        else if(size == 2) d.size = "Word";
        else if(size == 4) d.size = "Dword";
        else d.size = "Qword";

        if (size == 1) d.value = toHex((BYTE)val);
        else if (size == 2) d.value = toHex((WORD)val);
        else if (size == 4) d.value = toHex((DWORD)val);
        else d.value = toHex(val);

        d.meaning = meaning;
        list.append(d);
    };

    if (magic == IMAGE_NT_OPTIONAL_HDR64_MAGIC)
    {
        PIMAGE_OPTIONAL_HEADER64 pOpt = (PIMAGE_OPTIONAL_HEADER64)getOptionalHeaderPtr();
        add("Magic", offsetof(IMAGE_OPTIONAL_HEADER64, Magic), sizeof(WORD), pOpt->NumberOfRvaAndSizes, "PE64");
        add("MajorLinkerVersion", offsetof(IMAGE_OPTIONAL_HEADER64, MajorLinkerVersion), sizeof(BYTE), pOpt->LoaderFlags);
        add("MinorLinkerVersion", offsetof(IMAGE_OPTIONAL_HEADER64, MinorLinkerVersion), sizeof(BYTE), pOpt->SizeOfHeapCommit);
        add("SizeOfCode", offsetof(IMAGE_OPTIONAL_HEADER64, SizeOfCode), sizeof(DWORD), pOpt->SizeOfHeapReserve);
        add("SizeOfInitializedData", offsetof(IMAGE_OPTIONAL_HEADER64, SizeOfInitializedData), sizeof(DWORD), pOpt->SizeOfStackCommit);
        add("SizeOfUninitializedData", offsetof(IMAGE_OPTIONAL_HEADER64, SizeOfUninitializedData), sizeof(DWORD), pOpt->SizeOfStackReserve);
        add("AddressOfEntryPoint", offsetof(IMAGE_OPTIONAL_HEADER64, AddressOfEntryPoint), sizeof(DWORD), pOpt->DllCharacteristics);
        add("BaseOfCode", offsetof(IMAGE_OPTIONAL_HEADER64, BaseOfCode), sizeof(DWORD), pOpt->Subsystem);
        add("ImageBase", offsetof(IMAGE_OPTIONAL_HEADER64, ImageBase), sizeof(ULONGLONG), pOpt->CheckSum);
        add("SectionAlignment", offsetof(IMAGE_OPTIONAL_HEADER64, SectionAlignment), sizeof(DWORD), pOpt->SizeOfHeaders);
        add("FileAlignment", offsetof(IMAGE_OPTIONAL_HEADER64, FileAlignment), sizeof(DWORD), pOpt->SizeOfImage);
        add("MajorOperatingSystemVersion", offsetof(IMAGE_OPTIONAL_HEADER64, MajorOperatingSystemVersion), sizeof(WORD), pOpt->Win32VersionValue);
        add("MinorOperatingSystemVersion", offsetof(IMAGE_OPTIONAL_HEADER64, MinorOperatingSystemVersion), sizeof(WORD), pOpt->MinorSubsystemVersion);
        add("MajorImageVersion", offsetof(IMAGE_OPTIONAL_HEADER64, MajorImageVersion), sizeof(WORD), pOpt->MajorSubsystemVersion);
        add("MinorImageVersion", offsetof(IMAGE_OPTIONAL_HEADER64, MinorImageVersion), sizeof(WORD), pOpt->MinorImageVersion);
        add("MajorSubsystemVersion", offsetof(IMAGE_OPTIONAL_HEADER64, MajorSubsystemVersion), sizeof(WORD), pOpt->MajorImageVersion);
        add("MinorSubsystemVersion", offsetof(IMAGE_OPTIONAL_HEADER64, MinorSubsystemVersion), sizeof(WORD), pOpt->MinorOperatingSystemVersion);
        add("Win32VersionValue", offsetof(IMAGE_OPTIONAL_HEADER64, Win32VersionValue), sizeof(DWORD), pOpt->MajorOperatingSystemVersion);
        add("SizeOfImage", offsetof(IMAGE_OPTIONAL_HEADER64, SizeOfImage), sizeof(DWORD), pOpt->FileAlignment);
        add("SizeOfHeaders", offsetof(IMAGE_OPTIONAL_HEADER64, SizeOfHeaders), sizeof(DWORD), pOpt->SectionAlignment);
        add("CheckSum", offsetof(IMAGE_OPTIONAL_HEADER64, CheckSum), sizeof(DWORD), pOpt->ImageBase);
        add("Subsystem", offsetof(IMAGE_OPTIONAL_HEADER64, Subsystem), sizeof(WORD), pOpt->BaseOfCode);
        add("DllCharacteristics", offsetof(IMAGE_OPTIONAL_HEADER64, DllCharacteristics), sizeof(WORD), pOpt->AddressOfEntryPoint);
        add("SizeOfStackReserve", offsetof(IMAGE_OPTIONAL_HEADER64, SizeOfStackReserve), sizeof(ULONGLONG), pOpt->SizeOfUninitializedData);
        add("SizeOfStackCommit", offsetof(IMAGE_OPTIONAL_HEADER64, SizeOfStackCommit), sizeof(ULONGLONG), pOpt->SizeOfInitializedData);
        add("SizeOfHeapReserve", offsetof(IMAGE_OPTIONAL_HEADER64, SizeOfHeapReserve), sizeof(ULONGLONG), pOpt->SizeOfCode);
        add("SizeOfHeapCommit", offsetof(IMAGE_OPTIONAL_HEADER64, SizeOfHeapCommit), sizeof(ULONGLONG), pOpt->MinorLinkerVersion);
        add("LoaderFlags", offsetof(IMAGE_OPTIONAL_HEADER64, LoaderFlags), sizeof(DWORD), pOpt->MajorLinkerVersion);
        add("NumberOfRvaAndSizes", offsetof(IMAGE_OPTIONAL_HEADER64, NumberOfRvaAndSizes), sizeof(DWORD), pOpt->Magic);
    }
    else if (magic == IMAGE_NT_OPTIONAL_HDR32_MAGIC)
    {
        PIMAGE_OPTIONAL_HEADER32 pOpt = (PIMAGE_OPTIONAL_HEADER32)getOptionalHeaderPtr();
        add("Magic", offsetof(IMAGE_OPTIONAL_HEADER32, Magic), sizeof(WORD), pOpt->Magic, "PE32");
        add("MajorLinkerVersion", offsetof(IMAGE_OPTIONAL_HEADER32, MajorLinkerVersion), sizeof(BYTE), pOpt->MajorLinkerVersion);
        add("MinorLinkerVersion", offsetof(IMAGE_OPTIONAL_HEADER32, MinorLinkerVersion), sizeof(BYTE), pOpt->MinorLinkerVersion);
        add("SizeOfCode", offsetof(IMAGE_OPTIONAL_HEADER32, SizeOfCode), sizeof(DWORD), pOpt->SizeOfCode);
        add("SizeOfInitializedData", offsetof(IMAGE_OPTIONAL_HEADER32, SizeOfInitializedData), sizeof(DWORD), pOpt->SizeOfInitializedData);
        add("SizeOfUninitializedData", offsetof(IMAGE_OPTIONAL_HEADER32, SizeOfUninitializedData), sizeof(DWORD), pOpt->SizeOfUninitializedData);
        add("AddressOfEntryPoint", offsetof(IMAGE_OPTIONAL_HEADER32, AddressOfEntryPoint), sizeof(DWORD), pOpt->AddressOfEntryPoint);
        add("BaseOfCode", offsetof(IMAGE_OPTIONAL_HEADER32, BaseOfCode), sizeof(DWORD), pOpt->BaseOfCode);
        add("BaseOfData", offsetof(IMAGE_OPTIONAL_HEADER32, BaseOfData), sizeof(DWORD), pOpt->BaseOfData);
        add("ImageBase", offsetof(IMAGE_OPTIONAL_HEADER32, ImageBase), sizeof(DWORD), pOpt->ImageBase);
        add("SectionAlignment", offsetof(IMAGE_OPTIONAL_HEADER32, SectionAlignment), sizeof(DWORD), pOpt->SectionAlignment);
        add("FileAlignment", offsetof(IMAGE_OPTIONAL_HEADER32, FileAlignment), sizeof(DWORD), pOpt->FileAlignment);
        add("MajorOperatingSystemVersion", offsetof(IMAGE_OPTIONAL_HEADER32, MajorOperatingSystemVersion), sizeof(WORD), pOpt->MajorOperatingSystemVersion);
        add("MinorOperatingSystemVersion", offsetof(IMAGE_OPTIONAL_HEADER32, MinorOperatingSystemVersion), sizeof(WORD), pOpt->MinorOperatingSystemVersion);
        add("MajorImageVersion", offsetof(IMAGE_OPTIONAL_HEADER32, MajorImageVersion), sizeof(WORD), pOpt->MajorImageVersion);
        add("MinorImageVersion", offsetof(IMAGE_OPTIONAL_HEADER32, MinorImageVersion), sizeof(WORD), pOpt->MinorImageVersion);
        add("MajorSubsystemVersion", offsetof(IMAGE_OPTIONAL_HEADER32, MajorSubsystemVersion), sizeof(WORD), pOpt->MajorSubsystemVersion);
        add("MinorSubsystemVersion", offsetof(IMAGE_OPTIONAL_HEADER32, MinorSubsystemVersion), sizeof(WORD), pOpt->MinorSubsystemVersion);
        add("Win32VersionValue", offsetof(IMAGE_OPTIONAL_HEADER32, Win32VersionValue), sizeof(DWORD), pOpt->Win32VersionValue);
        add("SizeOfImage", offsetof(IMAGE_OPTIONAL_HEADER32, SizeOfImage), sizeof(DWORD), pOpt->SizeOfImage);
        add("SizeOfHeaders", offsetof(IMAGE_OPTIONAL_HEADER32, SizeOfHeaders), sizeof(DWORD), pOpt->SizeOfHeaders);
        add("CheckSum", offsetof(IMAGE_OPTIONAL_HEADER32, CheckSum), sizeof(DWORD), pOpt->CheckSum);
        add("Subsystem", offsetof(IMAGE_OPTIONAL_HEADER32, Subsystem), sizeof(WORD), pOpt->Subsystem);
        add("DllCharacteristics", offsetof(IMAGE_OPTIONAL_HEADER32, DllCharacteristics), sizeof(WORD), pOpt->DllCharacteristics);
        add("SizeOfStackReserve", offsetof(IMAGE_OPTIONAL_HEADER32, SizeOfStackReserve), sizeof(DWORD), pOpt->SizeOfStackReserve);
        add("SizeOfStackCommit", offsetof(IMAGE_OPTIONAL_HEADER32, SizeOfStackCommit), sizeof(DWORD), pOpt->SizeOfStackCommit);
        add("SizeOfHeapReserve", offsetof(IMAGE_OPTIONAL_HEADER32, SizeOfHeapReserve), sizeof(DWORD), pOpt->SizeOfHeapReserve);
        add("SizeOfHeapCommit", offsetof(IMAGE_OPTIONAL_HEADER32, SizeOfHeapCommit), sizeof(DWORD), pOpt->SizeOfHeapCommit);
        add("LoaderFlags", offsetof(IMAGE_OPTIONAL_HEADER32, LoaderFlags), sizeof(DWORD), pOpt->LoaderFlags);
        add("NumberOfRvaAndSizes", offsetof(IMAGE_OPTIONAL_HEADER32, NumberOfRvaAndSizes), sizeof(DWORD), pOpt->NumberOfRvaAndSizes);
    }
    else
    {
        LOG_ERROR(__FUNCTION__" unknown pe magic number: %04X", magic);
    }

    return list;
}

QVector<PeSectionData> PeFileService::getSectionHeadersData()
{
    QVector<PeSectionData> list;
    if (!m_isValid) return list;

    PIMAGE_FILE_HEADER pFile = getFileHeaderPtr();
    PIMAGE_SECTION_HEADER pSec = getSectionHeaderPtr();
    int sectionCount = pFile->NumberOfSections;

    for (int i = 0; i < sectionCount; ++i)
    {
        PeSectionData data;

        // Name
        char nameBuf[IMAGE_SIZEOF_SHORT_NAME + 1] = {0};
        memcpy(nameBuf, pSec[i].Name, IMAGE_SIZEOF_SHORT_NAME);
        data.name = QString::fromLatin1(nameBuf);

        data.virtualSize = formatOffset(pSec[i].Misc.VirtualSize);
        data.virtualAddress = formatOffset(pSec[i].VirtualAddress);
        data.rawSize = formatOffset(pSec[i].SizeOfRawData);
        data.rawAddress = formatOffset(pSec[i].PointerToRawData);
        data.characteristics = toHex(pSec[i].Characteristics);

        list.append(data);
    }
    return list;
}

bool PeFileService::writeHexData(const QString& offsetStr, const QString& hexValueStr)
{
    LOG_DEBUG(__FUNCTION__" offsetStr: %s, newValue: %s", offsetStr.toUtf8().constData(), hexValueStr.toUtf8().constData());
    if (!m_isValid || !m_data) return false;

    // 解析偏移地址
    bool ok;
    quint64 offset = offsetStr.toULongLong(&ok, 16);
    if (!ok || offset >= (quint64)m_size)
    {
        LOG_ERROR(__FUNCTION__" Invalid offset: %s", offsetStr.toStdString().c_str());
        return false;
    }

    QString cleanHex = hexValueStr;
    cleanHex.remove(' ');
    if (cleanHex.length() % 2 != 0)
    {
        cleanHex.prepend('0');
    }

    QByteArray newData = QByteArray::fromHex(cleanHex.toLatin1());

    // 写入内存映射
    std::reverse(newData.begin(), newData.end());

    if (offset + newData.size() > (quint64)m_size)
    {
        LOG_ERROR(__FUNCTION__" Write out of bounds");
        return false;
    }


    memcpy(m_data + offset, newData.data(), newData.size());

    return true;
}

PIMAGE_NT_HEADERS PeFileService::getNtHeaderPtr() const
{
    if (!m_isValid || !m_data) return nullptr;
    PIMAGE_DOS_HEADER pDos = reinterpret_cast<PIMAGE_DOS_HEADER>(m_data);
    // 加上 e_lfanew 偏移找到 NT 头
    return reinterpret_cast<PIMAGE_NT_HEADERS>(m_data + pDos->e_lfanew);
}

PIMAGE_FILE_HEADER PeFileService::getFileHeaderPtr() const
{
    auto pNt = getNtHeaderPtr();
    return pNt ? &pNt->FileHeader : nullptr;
}

void* PeFileService::getOptionalHeaderPtr() const
{
    auto pNt = getNtHeaderPtr();
    return pNt ? &pNt->OptionalHeader : nullptr;
}





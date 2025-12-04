#ifndef PEFILESERVICE_H
#define PEFILESERVICE_H

#include <QObject>
#include <QString>
#include <QFile>
#include <QVector>
#include <windows.h>
#include <QDateTime>


// 节表数据
struct PeSectionData
{
    QString name;
    QString virtualSize;
    QString virtualAddress;
    QString rawSize;
    QString rawAddress;
    QString characteristics;
};

struct PeFieldData
{
    QString member;
    QString offset;
    QString size;
    QString value;
    QString meaning;
};

class PeFileService : public QObject
{
    Q_OBJECT

public:
    PeFileService();
    ~PeFileService();

    // 加载文件
    bool loadPeFile(const QString& filePath);
    // 关闭文件
    void closePeFile();
    // 检查是否有效
    bool isValid() const;


    // --- 获取各部分数据的一系列方法开始 ---
    // --- 获取各部分数据的一系列方法开始 ---
    // --- 获取各部分数据的一系列方法开始 ---

    // 获取 DOS Header 数据
    QVector<PeFieldData> getDosHeaderData();
    QVector<PeFieldData> getNtHeaderData();
    QVector<PeFieldData> getFileHeaderData();
    QVector<PeFieldData> getOptionalHeaderData();
    QVector<PeSectionData> getSectionHeadersData();


    // --- 获取各部分数据的一系列方法结束 ---
    // --- 获取各部分数据的一系列方法结束 ---
    // --- 获取各部分数据的一系列方法结束 ---




    // 判断是否是 64 位程序
    bool is64Bit() const;

    // 获取 NT 头偏移方便跳转
    DWORD getNtHeadersOffset() const;

private:
    QFile m_file;
    uchar* m_data = nullptr; // 内存映射的首地址
    qint64 m_size = 0;
    bool m_isValid = false;

signals:
    void reqAfterLoadPeFileSuc(const QString& fileName);
    void reqAfterClosePeFileSuc();

public slots:
    bool writeHexData(const QString& offsetStr, const QString& hexValueStr);


    // helper
private:
    // 将数值转为 Hex 字符串
    template<typename T>
    QString toHex(T value, bool prefix = false)
    {
        // 2 * sizeof(T) 保证 1字节转2位Hex, 4字节转8位Hex
        return QString("%1").arg(value, sizeof(T) * 2, 16, QChar('0')).toUpper();
    }

    QString formatOffset(DWORD offset)
    {
        return QString("%1").arg(offset, 8, 16, QChar('0')).toUpper();
    }

    // 获取各个头的指针位置
    PIMAGE_NT_HEADERS getNtHeaderPtr() const;
    PIMAGE_FILE_HEADER getFileHeaderPtr() const;
    void* getOptionalHeaderPtr() const;
    PIMAGE_SECTION_HEADER getSectionHeaderPtr() const;

    // 格式化时间戳
    QString formatTimestamp(DWORD timestamp);
};





#endif // PEFILESERVICE_H

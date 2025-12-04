#ifndef LOGGER_H
#define LOGGER_H

#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <fstream>
#include <direct.h>
//#include <iostream>
#include <strstream>
#include <stdarg.h>
#include <vector>
#include <qDebug>
#include <ctime>
#include <mutex>

class Logger
{
public:
    enum Level
    {
        DEBUG,
        INFO,
        WARNING,
        ERR,
        FATAL,
    };

    struct Config
    {
        Level minLevel = Level::DEBUG;
        bool  toConsole = true;
        bool  toFile = false;
        std::string LogDir = "logs";
        std::string LogPrefix = "log";
    };

    static Logger& GetInstance()
    {
        static Logger Instance;
        return Instance;
    }

    void Init(const Config& config)
    {
        m_config = config;
        if (m_config.toFile)
        {
            OpenLogFile();
        }
    }

    void Log(Level level, const char* format, ...)
    {
        va_list argList;
        va_start(argList, format);
        std::string data = toFormatString(format, argList);
        va_end(argList);
        LogInternal(level, nullptr, 0, data.c_str());
    }

    void Log(Level level, const QString format, ...)
    {
        va_list argList;
        va_start(argList, format);
        std::string data = toFormatString(format, argList);
        va_end(argList);
        LogInternal(level, nullptr, 0, data.c_str());
    }


    void LogInternal(Level level, const char* fileName, int line, const char* format, ...)
    {
        if (level < m_config.minLevel)
            return;


        std::ostrstream str;

        str << "[" << GetLocalDateTime() << "]"
            << "[" << toLevelString(level) << "]";

        va_list argList;
        va_start(argList, format);
        std::string data = toFormatString(format, argList);
        va_end(argList);

        str << data << " ";
        if (fileName != nullptr)
        {
            str << fileName
                << "(" << line << ")";
        }
        str << std::endl << '\0';

        {
            std::lock_guard<std::mutex> Lock(logMutex);
            //打印控制台日志
            if (m_config.toConsole)
            {
                //            std::cout << str.str();
                qDebug() << str.str();
            }

            //打印文件日志
            if (m_config.toFile)
            {
                //检测文件时间
                if (GetLocalDate() != m_currentDate)
                {
                    OpenLogFile();
                }
                if (m_config.toFile)
                {
                    m_logFile << str.str();
                    m_logFile.flush();
                }
            }
        }

    }

    void OpenLogFile()
    {
        //创建目录
        _mkdir(m_config.LogDir.c_str());

        //获取时间
        std::string date = GetLocalDate();
        std::string fileName = m_config.LogDir + "//" + m_config.LogPrefix + "_" + date + ".log";

        //创建文件
        m_logFile.open(fileName, std::ios::out | std::ios::app);
        if (!m_logFile.is_open())
        {
            //            std::cout << "open:" << fileName << " error" << std::endl;
            qDebug() << "open:" << fileName.c_str() << " error";
            m_config.toFile = false;
            return;
        }
        m_currentDate = date;
    }

    Logger(const Logger& log) = delete;
    Logger& operator=(const Logger& log) = delete;
private:

    std::string toFormatString(const char* format, va_list argList)
    {
        int bytes = _vsnprintf(nullptr, 0, format, argList);
        std::vector<char> vec(bytes + 1);
        _vsnprintf(vec.data(), vec.size(), format, argList);
        return vec.data();
    }

    std::string toFormatString(const QString& format, va_list argList)
    {
        // QString -> UTF-8 char*
        QByteArray utf8Bytes = format.toUtf8();
        const char* cFormat = utf8Bytes.constData();
        int len = vsnprintf(nullptr, 0, cFormat, argList);
        std::vector<char> buf(len + 1);
        vsnprintf(buf.data(), buf.size(), cFormat, argList);
        return std::string(buf.data(), len);
    }

    std::string toLevelString(Level level)
    {
        switch (level)
        {
        case DEBUG:
            return "DEBUG";
        case INFO:
            return "INFO";
        case WARNING:
            return "WARNING";
        case ERR:
            return "ERROR";
        case FATAL:
            return "FATAL";
        default:
            return "UNKOWN";
        }
    }

    std::string GetLocalDate()
    {
        time_t now = std::time(nullptr);
        tm* tm = std::localtime(&now);
        char date[20];
        std::strftime(date, sizeof(date), "%Y_%m_%d", tm);
        return date;
    }
    std::string GetLocalDateTime()
    {
        time_t now = std::time(nullptr);
        tm* tm = std::localtime(&now);
        char dateTime[80];
        std::strftime(dateTime, sizeof(dateTime), "%Y-%m-%d %H:%M:%S", tm);
        return dateTime;
    }

    Logger() = default;
    ~Logger() = default;
    Config m_config;
    std::ofstream m_logFile;
    std::string m_currentDate;
    std::mutex logMutex;
};

#define LOG_DEBUG(format, ...) Logger::GetInstance().Log(Logger::DEBUG, format, __VA_ARGS__);
#define LOG_INFO(format, ...) Logger::GetInstance().Log(Logger::INFO, format, __VA_ARGS__);
#define LOG_WARNING(format, ...) Logger::GetInstance().Log(Logger::WARNING, format, __VA_ARGS__);
#define LOG_ERROR(format, ...) Logger::GetInstance().Log(Logger::ERR, format, __VA_ARGS__);
#define LOG_FATAL(format, ...) Logger::GetInstance().Log(Logger::FATAL, format, __VA_ARGS__);

#define LOGF_DEBUG(format, ...) Logger::GetInstance().LogInternal(Logger::DEBUG, __FILE__, __LINE__, format, __VA_ARGS__);
#define LOGF_INFO(format, ...) Logger::GetInstance().LogInternal(Logger::INFO, __FILE__, __LINE__, format,  __VA_ARGS__);
#define LOGF_WARNING(format, ...) Logger::GetInstance().LogInternal(Logger::WARNING, __FILE__, __LINE__, format,  __VA_ARGS__);
#define LOGF_ERROR(format, ...) Logger::GetInstance().LogInternal(Logger::ERROR, __FILE__, __LINE__, format,  __VA_ARGS__);
#define LOGF_FATAL(format, ...) Logger::GetInstance().LogInternal(Logger::FATAL, __FILE__, __LINE__, format, __VA_ARGS__);


#endif // LOGGER_H

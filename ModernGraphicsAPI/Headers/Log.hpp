#pragma once

#include <filesystem>
#include <fstream>
#include <string>

enum class LogLevel : unsigned int
{
    None,
    Notification,
    Debug,
    Test,
    Warning,
    Critical
};

class Log
{
    // Attributes
private:
    static std::ofstream logFile;

    // Methods
public:
    static void OpenFile(std::filesystem::path const& p_filenName);
    static void Print(const std::string& p_log, const LogLevel& p_level);
    static void CloseFile();
};

#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

void DebugLog(const std::string& p_filename, const unsigned int p_line, const std::string& p_functionName, const std::string p_log);

#define DEBUG_LOG(p_log) DebugLog(__FILENAME__, __LINE__, __FUNCTION__, p_log);
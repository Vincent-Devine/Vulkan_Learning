#include "Log.hpp"

#include <iostream>
#include <Windows.h>
#include <debugapi.h>

#include "Assertion.hpp"

void DebugLog(const std::string& p_filename, const unsigned int p_line, const std::string& p_functionName, const std::string p_log)
{
    std::string message = p_filename + '(' + std::to_string(p_line) + "): " + p_functionName + ": " + p_log;
    OutputDebugStringA(message.c_str());
    Log::Print(message, LogLevel::Debug);
}

std::ofstream Log::logFile;
	
void Log::OpenFile(std::filesystem::path const& p_filename)
{
    if (logFile && logFile.is_open())
    {
        Log::Print("Log file already open", LogLevel::Warning);
        return;
    }

    logFile.open(p_filename, std::ios::out);
    if (!logFile)
        Log::Print("Fail to open log file " + p_filename.string(), LogLevel::Warning);
    else
        Log::Print("Open log file " + p_filename.string(), LogLevel::Notification);
}

void Log::Print(const std::string& p_log, const LogLevel& p_level)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    std::string log;

    switch (p_level)
    {
    case LogLevel::Notification:
        SetConsoleTextAttribute(handle, 11); // blue
        std::cout << "[Notification]";
        SetConsoleTextAttribute(handle, 15); // white (default)
        std::cout << " " << p_log << std::endl;
        log = "[Notification] " + p_log + '\n';
        break;

    case LogLevel::Debug:
        SetConsoleTextAttribute(handle, 13); // pink
        std::cout << "[Debug]";
        SetConsoleTextAttribute(handle, 15); // white (default)
        std::cout << " " << p_log << std::endl;
        log = "[Debug] " + p_log + '\n';
        break;

    case LogLevel::Test:
        SetConsoleTextAttribute(handle, 10); // green
        std::cout << "[Test]";
        SetConsoleTextAttribute(handle, 15); // white (default)
        std::cout << " " << p_log << std::endl;;
        log = "[Test] " + p_log + '\n';
        break;

    case LogLevel::Warning:
        SetConsoleTextAttribute(handle, 14); // yellow
        std::cout << "[Warning]";
        SetConsoleTextAttribute(handle, 15); // white (default)
        std::cout << " " << p_log << std::endl;;
        log = "[Warning] " + p_log + '\n';
        break;

    case LogLevel::Critical:
        SetConsoleTextAttribute(handle, 207); // red
        std::cout << "[Critical]";
        SetConsoleTextAttribute(handle, 15); // white (default)
        std::cout << " " << p_log << std::endl;;
        log = "[Critical] " + p_log + '\n';
        break;

    default:
        std::cout << p_log << std::endl;;
        log = p_log + '\n';
        break;
    }

    if(logFile.is_open())
        logFile << log;
}

void Log::CloseFile()
{
    logFile.close();
    Log::Print("Close log file", LogLevel::Notification);
}

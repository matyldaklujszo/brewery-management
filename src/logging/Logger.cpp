#include <iostream>
#include "Logger.h"
#include "LogHelpers.h"

using namespace brewery;

std::unique_ptr<Output> Logger::output_ = nullptr;
Logger::LogLevel Logger::logLevel_ = Logger::LogLevel::INFO;
std::array<std::string, 4> Logger::logLevelNames_ = { "DEBUG",
                                                      "INFO",
                                                      "WARNING",
                                                      "ERROR"};

void
Logger::setLogLevel(Logger::LogLevel logLevel)
{
    logLevel_ = logLevel;
}

void
Logger::log(Logger::LogLevel logLevel, const std::string& str)
{
    if (logLevel >= logLevel_ && output_)
    {
        output_->write(str);
    }
}

void
Logger::setOutput(std::unique_ptr<Output> output)
{
    output_ = std::move(output);
}

void
Logger::setLogLevel(const std::string& logLevelStr)
{
    if (logLevelStr == "DEBUG")
    {
        setLogLevel(LogLevel::DEBUG);
    }
    else if (logLevelStr == "INFO")
    {
        setLogLevel(LogLevel::INFO);
    }
    else if (logLevelStr == "WARNING")
    {
        setLogLevel(LogLevel::WARNING);
    }
    else if (logLevelStr == "ERROR")
    {
        setLogLevel(LogLevel::ERROR);
    }
    else
    {
        LOG_WARNING("LogLevel=" << logLevelStr << " does not exist");
    }
}

std::string
Logger::getLogLevel()
{
    return logLevelNames_[static_cast<int>(logLevel_)];
}

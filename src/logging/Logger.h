#ifndef BREWERY_MANAGEMENT_LOGGER_H
#define BREWERY_MANAGEMENT_LOGGER_H

#include <memory>
#include <file/Output.h>

namespace brewery {
class Logger {
public:
    enum class LogLevel {
        DEBUG,
        INFO,
        WARNING,
        ERROR
    };
    static void setLogLevel(const std::string&);
    static void setLogLevel(LogLevel);
    static std::string getLogLevel();
    static void setOutput(std::unique_ptr<Output>);
    static void log(LogLevel, const std::string&);
private:
    static std::unique_ptr<Output> output_;
    static LogLevel logLevel_;
    static std::array<std::string, 4> logLevelNames_;
};
}

#endif //BREWERY_MANAGEMENT_LOGGER_H

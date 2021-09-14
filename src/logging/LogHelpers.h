#ifndef BREWERY_MANAGEMENT_LOGHELPERS_H
#define BREWERY_MANAGEMENT_LOGHELPERS_H

#include <logging/Logger.h>
#include <utils/Time.h>
#include <sstream>

namespace brewery {

#define LOG(level, logLevelStr, stream) { \
    std::stringstream ss;       \
    ss << "[" << (logLevelStr) << "][" << getCurrentTime() << "][" << (const char*)__FILE__ << ":" << (const int)__LINE__    \
    << "] " << stream << '\n'; \
    Logger::log(level, ss.str());  \
}

#define LEVEL_DEBUG "DEBUG"
#define LEVEL_INFO "INFO"
#define LEVEL_WARNING "WARNING"
#define LEVEL_ERROR "ERROR"

#define LOG_DEBUG(stream) LOG(Logger::LogLevel::DEBUG, LEVEL_DEBUG, stream)
#define LOG_INFO(stream) LOG(Logger::LogLevel::INFO, LEVEL_INFO, stream)
#define LOG_WARNING(stream) LOG(Logger::LogLevel::WARNING, LEVEL_WARNING, stream)
#define LOG_ERROR(stream) LOG(Logger::LogLevel::ERROR, LEVEL_ERROR, stream)
}
#endif //BREWERY_MANAGEMENT_LOGHELPERS_H

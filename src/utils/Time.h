#ifndef BREWERY_MANAGEMENT_NEWER_TIME_H
#define BREWERY_MANAGEMENT_NEWER_TIME_H

#include <ctime>
#include <cstring>

namespace brewery {

#ifdef _WIN32
inline std::string getTime() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    std::string hour, minute, second, day, month, year;
    if(ltm->tm_hour < 10)
        hour = "0" + std::to_string(ltm->tm_hour);
    else
        hour = std::to_string(ltm->tm_hour);

    if(ltm->tm_min < 10)
        minute = "0" + std::to_string(ltm->tm_min);
    else
        minute = std::to_string(ltm->tm_min);

    if(ltm->tm_sec < 10)
        second = "0" + std::to_string(ltm->tm_sec);
    else
        second = std::to_string(ltm->tm_sec);

    if(ltm->tm_mday < 10)
        day = "0" + std::to_string(ltm->tm_mday);
    else
        day = std::to_string(ltm->tm_mday);

    if(ltm->tm_mon < 10)
        month = "0" + std::to_string(ltm->tm_mon);
    else
        month = std::to_string(ltm->tm_mon);

    year = std::to_string(1900 + ltm->tm_year);
    std::string date = hour + ":" + minute + ":" + second + "   " + day + "-" + month + "-" + year;
    return date;
}
#else
inline std::string
getCurrentTime()
{
   std::time_t time = std::time(nullptr);
   auto time_str = std::ctime(&time);
   time_str[std::strcspn(time_str, "\n")] = '\0';
   return time_str;
}
#endif
}
#endif //BREWERY_MANAGEMENT_NEWER_TIME_H

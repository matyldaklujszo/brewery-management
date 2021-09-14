#ifndef BREWERY_MANAGEMENT_SOURCE_H
#define BREWERY_MANAGEMENT_SOURCE_H

#include <rapidjson/document.h>

namespace brewery {
class Source {
public:
    virtual ~Source() = default;
    virtual std::string& str() = 0;
protected:
    std::string str_;
};
}

#endif //BREWERY_MANAGEMENT_SOURCE_H

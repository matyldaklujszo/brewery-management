#ifndef BREWERY_MANAGEMENT_OUTPUT_H
#define BREWERY_MANAGEMENT_OUTPUT_H

#include <string>

namespace brewery {
class Output {
public:
    virtual ~Output() = default;
    virtual void write(const std::string&) const = 0;
};
}

#endif //BREWERY_MANAGEMENT_OUTPUT_H

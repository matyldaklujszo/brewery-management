#ifndef BREWERY_MANAGEMENT_SERVICE_H
#define BREWERY_MANAGEMENT_SERVICE_H

#include <memory>
#include <file/Source.h>

namespace brewery {
class Service
{
public:
    Service() = default;
    virtual ~Service() = default;

    virtual void load(std::shared_ptr<Source>) = 0;
};
} // namespace

#endif //BREWERY_MANAGEMENT_SERVICE_H

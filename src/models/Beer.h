#ifndef BREWERY_MANAGEMENT_BEER_H
#define BREWERY_MANAGEMENT_BEER_H

#include <string>

namespace brewery {
class Beer {
public:
    Beer() = delete;
    explicit Beer(const std::string& name);

    std::string getName() const;
private:
    std::string name_;
};

} // namespace

#endif //BREWERY_MANAGEMENT_BEER_H

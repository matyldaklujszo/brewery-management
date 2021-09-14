#ifndef BREWERY_MANAGEMENT_CUSTOMER_H
#define BREWERY_MANAGEMENT_CUSTOMER_H

#include <string>

namespace brewery {
class Customer
{
public:
    Customer() = default;
    explicit Customer(const std::string&);

    std::string getName() const;
    void setName(const std::string&);
private:
    std::string name_;
};
}

#endif //BREWERY_MANAGEMENT_CUSTOMER_H

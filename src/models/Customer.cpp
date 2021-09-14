#include "Customer.h"

using namespace brewery;

Customer::Customer(const std::string& name) :
    name_(name)
{}

std::string
Customer::getName() const
{
    return name_;
}

void
Customer::setName(const std::string& name)
{
    name_ = name;
}

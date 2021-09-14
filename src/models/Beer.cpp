#include "Beer.h"

using namespace brewery;

Beer::Beer(const std::string& name) :
    name_(name)
{}

std::string
Beer::getName() const {
    return name_;
}

#include "FileSource.h"

#include <sstream>
using namespace brewery;

FileSource::FileSource(const std::string& path)
{
    open(path);
}

std::string& FileSource::str() {
    return str_;
}

void FileSource::open(const std::string& path)
{
    std::ifstream stream{path};
    std::stringstream buffer;
    buffer << stream.rdbuf();
    str_ = buffer.str();
}

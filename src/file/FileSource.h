#ifndef BREWERY_MANAGEMENT_FILESOURCE_H
#define BREWERY_MANAGEMENT_FILESOURCE_H

#include <rapidjson/document.h>
#include <string>
#include <fstream>
#include <optional>
#include "file/Source.h"

namespace brewery {
class FileSource : public Source
{
public:
    FileSource() = default;
    explicit FileSource(const std::string&);
    ~FileSource() override = default;

    void open(const std::string&);
    std::string& str() override;
};
} // namespace
#endif //BREWERY_MANAGEMENT_FILESOURCE_H

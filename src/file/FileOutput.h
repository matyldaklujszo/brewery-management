#ifndef BREWERY_MANAGEMENT_FILEOUTPUT_H
#define BREWERY_MANAGEMENT_FILEOUTPUT_H

#include <string>
#include <streambuf>
#include "Output.h"

namespace brewery {
class FileOutput : public Output {
public:
    FileOutput() = delete;
    explicit FileOutput(const std::string&, bool trunc = false);
    ~FileOutput() override = default;

    void write(const std::string&) const override;

private:
    std::string path_;
};
}

#endif //BREWERY_MANAGEMENT_FILEOUTPUT_H

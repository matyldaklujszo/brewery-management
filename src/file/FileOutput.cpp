#include <fstream>
#include <iostream>
#include "FileOutput.h"

using namespace brewery;

FileOutput::FileOutput(const std::string& path, bool trunc) :
    path_(path)
{
    if (trunc)
    {
        std::ofstream ofs{path_};
        ofs.close();
    }
}

void FileOutput::write(const std::string& str) const
{
    // TODO check if good!
    std::fstream ofs{path_, std::ios_base::app};
    ofs << str;
    ofs.close();
}

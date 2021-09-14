#include <json/ConfigJson.h>
#include <file/FileSource.h>
#include "ConfigLoader.h"
#include "Constants.h"

using namespace brewery;

Config ConfigLoader::load()
{
    Config config;
    ConfigJson cfgJson;
    FileSource fs{constants::CONFIG_PATH};
    FileSource schema_fs{constants::CONFIG_SCHEMA_PATH};

    rapidjson::Document doc;
    doc.Parse(fs.str().c_str());
    cfgJson.setSchema(schema_fs.str());
    cfgJson.load(config, doc);

    return config;
}

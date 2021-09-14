#include "json/ConfigJson.h"

using namespace std::placeholders;
using namespace brewery;

void
ConfigJson::load(Config& cfg, rapidjson::Document& doc)
{
    validate(doc);

    setMember(doc, "beerPath", std::bind(&Config::setBeerStocksPath, &cfg, _1));
    setMember(doc, "beerSchemaPath", std::bind(&Config::setBeerStocksSchemaPath, &cfg, _1));
    setMember(doc, "ordersPath", std::bind(&Config::setOrdersPath, &cfg, _1));
    setMember(doc, "ordersSchemaPath", std::bind(&Config::setOrdersSchemaPath, &cfg, _1));
    setMember(doc, "logPath", std::bind(&Config::setLogPath, &cfg, _1));
    setMember(doc, "logLevel", std::bind(&Config::setLogLevel, &cfg, _1));
}

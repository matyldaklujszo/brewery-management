#ifndef BREWERY_MANAGEMENT_CONFIGJSON_H
#define BREWERY_MANAGEMENT_CONFIGJSON_H

#include <functional>
#include <rapidjson/document.h>
#include <json/Json.h>
#include "utils/Config.h"

namespace brewery {
class ConfigJson : public Json {
public:
    ConfigJson() = default;
    ~ConfigJson() override = default;

    void load(Config&, rapidjson::Document&);
};
}

#endif //BREWERY_MANAGEMENT_CONFIGJSON_H

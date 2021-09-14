#ifndef BREWERY_MANAGEMENT_CONFIGLOADER_H
#define BREWERY_MANAGEMENT_CONFIGLOADER_H

#include "Config.h"

namespace brewery {
class ConfigLoader {
public:
    static Config load();
};
}

#endif //BREWERY_MANAGEMENT_CONFIGLOADER_H

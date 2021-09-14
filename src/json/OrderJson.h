#ifndef BREWERY_MANAGEMENT_ORDERJSON_H
#define BREWERY_MANAGEMENT_ORDERJSON_H

#include "Json.h"
#include <models/Order.h>

namespace brewery {
    class OrderJson : public Json {
    public:
        OrderJson() = default;
        ~OrderJson() override = default;

        void load(std::vector<std::shared_ptr<Order>>&, const rapidjson::Document&) const;
        void toJson(std::vector<std::shared_ptr<Order>>&, rapidjson::Document&) const;

//        void addToJson(std::vector<Stock<Beer>> &, rapidjson::Document &, std::string, int,
//                       std::string, std::string, std::string) const;
    };
}

#endif //BREWERY_MANAGEMENT_ORDERJSON_H

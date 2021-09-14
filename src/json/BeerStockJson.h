#ifndef BREWERY_MANAGEMENT_BEERSTOCKJSON_H
#define BREWERY_MANAGEMENT_BEERSTOCKJSON_H

#include <models/Stock.h>
#include <models/Beer.h>
#include "Json.h"

namespace brewery {
class BeerStockJson : public Json {
public:
    BeerStockJson() = default;
    ~BeerStockJson() override = default;

    void load(std::vector<std::shared_ptr<Stock<Beer>>>&, const rapidjson::Document&) const;
    void toJson(std::vector<std::shared_ptr<Stock<Beer>>>&, rapidjson::Document&) const;
};
}
#endif //BREWERY_MANAGEMENT_BEERSTOCKJSON_H

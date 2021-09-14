#include "BeerStockJson.h"

using namespace brewery;

void
BeerStockJson::load(std::vector<std::shared_ptr<Stock<Beer>>>& beerStocks, const rapidjson::Document& doc) const
{
    validate(doc);

    auto itr = doc.FindMember("stocks");
    if (itr != doc.MemberEnd() && itr->value.IsArray())
    {
        for (auto& stock : itr->value.GetArray())
        {
            // TODO setMember...
            Beer b{stock["beer"].GetObject()["name"].GetString()};
            beerStocks.emplace_back(std::make_shared<Stock<Beer>>(b, stock["quantity"].GetInt(), stock["singularPrice"].GetDouble()));
        }
    }
}

void
BeerStockJson::toJson(std::vector<std::shared_ptr<Stock<Beer>>>& beerStocks, rapidjson::Document& doc) const
{
    doc.SetObject();
    auto allocator = doc.GetAllocator();

    rapidjson::Value beerStockArray{rapidjson::kArrayType};
    for (auto& stock : beerStocks)
    {
        rapidjson::Value stockVal{rapidjson::kObjectType};
        rapidjson::Value v;
        v.SetInt(stock->getQuantity());
        stockVal.AddMember("quantity", v, allocator);

        v.SetDouble(stock->getSingularPrice());
        stockVal.AddMember("singularPrice", v, allocator);

        rapidjson::Value beerVal{rapidjson::kObjectType};
        v.SetString(stock->getProduct().getName().c_str(), allocator);
        beerVal.AddMember("name", v, allocator);
        stockVal.AddMember("beer", beerVal, allocator);
        beerStockArray.PushBack(stockVal, allocator);
    }

    doc.AddMember("stocks", beerStockArray, allocator);
    validate(doc);
}

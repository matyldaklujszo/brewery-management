#include "OrderJson.h"
#include "BeerStockJson.h"
#include <iostream>
#include <logging/LogHelpers.h>

using namespace brewery;

void
OrderJson::load(std::vector<std::shared_ptr<Order>>& orders, const rapidjson::Document& doc) const
{
    validate(doc);

    auto itr = doc.FindMember("orders");
    if (itr != doc.MemberEnd() && itr->value.IsArray())
    {
        for (auto& order : itr->value.GetArray())
        {
            std::vector<ProductQuantityPair<Beer>> beerList;
            auto beerListItr = order.FindMember("products");
            if (beerListItr != order.MemberEnd() && beerListItr->value.IsArray())
            {
                for (auto& stock : beerListItr->value.GetArray())
                {
                    Beer b{stock["beer"].GetObject()["name"].GetString()};
                    beerList.emplace_back(b, stock["quantity"].GetInt());
                }
            }

            Order newOrder = Order::create().products(beerList)
                                .placed(order["orderDate"].GetString())
                                .by(Customer(order["customer"].GetString()));

            auto completionDateItr = order.FindMember("completionDate");
            if (completionDateItr != order.MemberEnd() && completionDateItr->value.IsString())
            {
                newOrder = Order::update(newOrder).completed(completionDateItr->value.GetString());
            }

            orders.push_back(std::make_shared<Order>(newOrder));
        }
    }
}

void
OrderJson::toJson(std::vector<std::shared_ptr<Order>>& orders, rapidjson::Document& doc) const
{
    doc.SetObject();
    auto allocator = doc.GetAllocator();

    rapidjson::Value ordersArray{rapidjson::kArrayType};
    for (auto& order : orders)
    {
        rapidjson::Value orderVal{rapidjson::kObjectType};

        rapidjson::Value orderedBeerArray{rapidjson::kArrayType};
        for (auto& orderedBeer : order->getOrderedProducts())
        {
            rapidjson::Value stockVal{rapidjson::kObjectType};
            rapidjson::Value v;
            v.SetInt(orderedBeer.quantity_);
            stockVal.AddMember("quantity", v, allocator);

            rapidjson::Value beerVal{rapidjson::kObjectType};
            v.SetString(orderedBeer.product_.getName().c_str(), allocator);
            beerVal.AddMember("name", v, allocator);
            stockVal.AddMember("beer", beerVal, allocator);
            orderedBeerArray.PushBack(stockVal, allocator);
        }
        orderVal.AddMember("products", orderedBeerArray, allocator);

        rapidjson::Value v;
        v.SetString(order->getCustomer().getName().c_str(), allocator);
        orderVal.AddMember("customer", v, allocator);

        v.SetString(order->getOrderDate().c_str(), allocator);
        orderVal.AddMember("orderDate", v, allocator);

        if (order->isCompleted())
        {
            v.SetString(order->getCompletionDate().c_str(), allocator);
            orderVal.AddMember("completionDate", v, allocator);
        }

        ordersArray.PushBack(orderVal, allocator);
    }

    doc.AddMember("orders", ordersArray, allocator);
    validate(doc);
}
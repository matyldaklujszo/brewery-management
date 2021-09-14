#include <iostream>
#include <logging/LogHelpers.h>
#include "OrderService.h"

using namespace brewery;

OrderService::OrderService(Database& db) :
    db_(db)
{}

void OrderService::load(std::shared_ptr<Source> src)
{
    rapidjson::Document doc;
    doc.Parse(src->str().c_str());
    orderJson_.load(db_.orders_, doc);
}

void OrderService::save(std::shared_ptr<Output> output)
{
    rapidjson::Document doc;
    orderJson_.toJson(db_.orders_, doc);
    output->write(Json::doc2str(doc));
}

std::shared_ptr<Order>
OrderService::getById(int id)
{
    auto comparator = [&id](const std::shared_ptr<Order>& order)
    {
        return order->getId() == id;
    };

    auto order = std::find_if(db_.orders_.begin(), db_.orders_.end(), comparator);
    return *order;
}

std::vector<std::shared_ptr<Order>>&
OrderService::getAll()
{
    return db_.orders_;
}

void
OrderService::addOrder(const std::shared_ptr<Order>& newOrder)
{
    LOG_INFO("New Order #" << newOrder->getId() << " added");
    db_.orders_.push_back(newOrder);
}

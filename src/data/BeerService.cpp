#include <iostream>
#include <logging/LogHelpers.h>
#include "BeerService.h"

using namespace brewery;

BeerService::BeerService(Database& db) :
    db_(db)
{}

void
BeerService::load(std::shared_ptr<Source> src)
{
    LOG_INFO("LOAD BEER STOCKS START");
    rapidjson::Document doc;
    doc.Parse(src->str().c_str());
    beerStockJson_.load(db_.beerStocks_, doc);
    LOG_INFO("LOAD BEER STOCKS END");
}

std::shared_ptr<Stock<Beer>>
BeerService::getStockByBeerName(const std::string& name)
{
    auto comparator = [&name](const std::shared_ptr<Stock<Beer>>& stock)
            {
                return stock->getProduct().getName() == name;
            };
    auto stock = std::find_if(db_.beerStocks_.begin(), db_.beerStocks_.end(), comparator);
    // TODO what to return if stock not found???
    return *stock;
}

std::shared_ptr<Stock<Beer>>
BeerService::getStockByIndex(const int index)
{
    return db_.beerStocks_[index];
    // TODO check if not overflow
}

void
BeerService::save(std::shared_ptr<Output> output)
{
    rapidjson::Document doc;
    beerStockJson_.toJson(db_.beerStocks_, doc);
    output->write(Json::doc2str(doc));
}

std::vector<std::shared_ptr<Stock<Beer>>>&
BeerService::getAll()
{
    return db_.beerStocks_;
}

void
BeerService::addStock(std::shared_ptr<Stock<Beer>>& stock)
{
    db_.beerStocks_.push_back(stock);
}

void
BeerService::deleteByName(const std::string& name)
{
    auto comparator = [&name](const std::shared_ptr<Stock<Beer>>& stock)
    {
        return stock->getProduct().getName() == name;
    };
    auto stock = std::find_if(db_.beerStocks_.begin(), db_.beerStocks_.end(), comparator);

    db_.beerStocks_.erase(stock);
    LOG_INFO("Stock deleted. Size = " << db_.beerStocks_.size());
}

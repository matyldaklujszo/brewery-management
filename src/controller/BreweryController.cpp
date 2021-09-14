#include <file/FileSource.h>
#include <file/FileOutput.h>
#include <iostream>
#include <set>
#include <logging/LogHelpers.h>
#include "BreweryController.h"

using namespace brewery;

BreweryController::BreweryController(const Config& cfg, Database& db) :
        config_(cfg),
        beerService_(db),
        orderService_(db)
{}

void
BreweryController::loadAll()
{
    LOG_INFO("Loading jsons...");
    auto fs = std::make_shared<FileSource>(config_.getBeerStocksPath());
    if (config_.isSetBeerStocksSchemaPath())
    {
        LOG_INFO("Setting BeerStock schema");
        FileSource schemaFs{config_.getBeerStocksSchemaPath()};
        beerService_.beerStockJson_.setSchema(schemaFs.str());
    }
    beerService_.load(fs);

    fs->open(config_.getOrdersPath());
    if (config_.isSetOrdersSchemaPath())
    {
        LOG_INFO("Setting Orders schema");
        FileSource schemaFs{config_.getOrdersSchemaPath()};
        orderService_.orderJson_.setSchema(schemaFs.str());
    }
    orderService_.load(fs);
    LOG_INFO("Loading jsons finished");
}

std::vector<std::shared_ptr<Stock<Beer>>>&
BreweryController::getAllBeerStocks()
{
    return beerService_.getAll();
}

std::vector<std::shared_ptr<Order>>&
BreweryController::getAllOrders()
{
    return orderService_.getAll();
}

bool
BreweryController::canOrderBeCompleted(int id)
{
    auto order = orderService_.getById(id);

    if (order->isCompleted())
    {
        return false;
    }

    for (auto& orderedBeer : order->getOrderedProducts())
    {
        auto stock = beerService_.getStockByBeerName(orderedBeer.product_.getName());
        if (stock->getQuantity() < orderedBeer.quantity_)
        {
            return false;
        }
    }

    return true;
}

std::shared_ptr<Stock<Beer>>
BreweryController::getStockByBeerName(const std::string& name)
{
    return beerService_.getStockByBeerName(name);
}

void
BreweryController::saveAll()
{
    LOG_INFO("Saving jsons...");
    auto fo = std::make_shared<FileOutput>(config_.getOrdersPath(), true);
    orderService_.save(fo);

    fo = std::make_shared<FileOutput>(config_.getBeerStocksPath(), true);
    beerService_.save(fo);
}

std::vector<std::string>
BreweryController::getUniqueBeerNames()
{
    std::set<std::string> uniqueNames;
    for (auto& stock : beerService_.getAll())
    {
        uniqueNames.insert(stock->getProduct().getName());
    }
    return {uniqueNames.begin(), uniqueNames.end()};
}

void
BreweryController::addOrder(const std::shared_ptr<Order>& newOrder)
{
    orderService_.addOrder(newOrder);
}

std::shared_ptr<Order>
BreweryController::getOrderById(int id)
{
    return orderService_.getById(id);
}

void
BreweryController::completeOrder(int id)
{
    auto order = getOrderById(id);
    order->complete();

    for (auto& orderItem : order->getOrderedProducts())
    {
        auto stock = beerService_.getStockByBeerName(orderItem.product_.getName());
        stock->subtract(orderItem.quantity_);
    }
}

void
BreweryController::addBeerStock(std::shared_ptr<Stock<Beer>> stock)
{
    beerService_.addStock(stock);
}

void
BreweryController::deleteBeerStockByName(const std::string& name)
{
    beerService_.deleteByName(name);
}

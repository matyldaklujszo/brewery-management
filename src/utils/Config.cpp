#include "Config.h"

using namespace brewery;

void
Config::setBeerStocksPath(const std::string& path)
{
    beerStocksPath_ = path;
}

std::string
Config::getBeerStocksPath() const
{
    return beerStocksPath_;
}

void
Config::setBeerStocksSchemaPath(const std::string& path)
{
    beerStocksSchemaPath_ = path;
}

std::string
Config::getBeerStocksSchemaPath() const
{
    return beerStocksSchemaPath_.value();
}

bool
Config::isSetBeerStocksSchemaPath() const
{
    return std::nullopt != beerStocksSchemaPath_;
}

void
Config::setOrdersPath(const std::string& path)
{
    ordersPath_ = path;
}

std::string
Config::getOrdersPath() const
{
    return ordersPath_;
}

void
Config::setOrdersSchemaPath(const std::string& path)
{
    ordersSchemaPath_ = path;
}

std::string
Config::getOrdersSchemaPath() const
{
    return ordersSchemaPath_.value();
}

bool
Config::isSetOrdersSchemaPath() const
{
    return std::nullopt != ordersSchemaPath_;
}

void
Config::setLogPath(const std::string& path)
{
    logPath_ = path;
}

std::string
Config::getLogPath() const
{
    return logPath_;
}

bool
Config::isSetLogLevel() const
{
    return std::nullopt != logLevel_;
}

void
Config::setLogLevel(const std::string& logLevel)
{
    logLevel_ = logLevel;
}

std::string
Config::getLogLevel() const
{
    return logLevel_.value();
}

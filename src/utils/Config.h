#ifndef BREWERY_MANAGEMENT_CONFIG_H
#define BREWERY_MANAGEMENT_CONFIG_H

#include <string>
#include <optional>
#include <logging/Logger.h>

namespace brewery {
class Config {
public:
    Config() = default;
    ~Config() = default;
    Config(const Config&) = default;
    Config& operator=(const Config&) = default;

    void setBeerStocksPath(const std::string&);
    std::string getBeerStocksPath() const;
    void setBeerStocksSchemaPath(const std::string&);
    std::string getBeerStocksSchemaPath() const;
    bool isSetBeerStocksSchemaPath() const;
    void setOrdersPath(const std::string&);
    std::string getOrdersPath() const;
    void setOrdersSchemaPath(const std::string&);
    std::string getOrdersSchemaPath() const;
    bool isSetOrdersSchemaPath() const;
    void setLogPath(const std::string&);
    std::string getLogPath() const;
    bool isSetLogLevel() const;
    void setLogLevel(const std::string&);
    std::string getLogLevel() const;
private:
    std::string beerStocksPath_;
    std::optional<std::string> beerStocksSchemaPath_;
    std::string ordersPath_;
    std::optional<std::string> ordersSchemaPath_;
    std::string logPath_;
    std::optional<std::string> logLevel_;
};
}
#endif //BREWERY_MANAGEMENT_CONFIG_H

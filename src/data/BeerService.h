#ifndef BREWERY_MANAGEMENT_BEERSERVICE_H
#define BREWERY_MANAGEMENT_BEERSERVICE_H

#include "Database.h"
#include "Service.h"
#include <utils/Config.h>
#include <json/BeerStockJson.h>
#include <file/Output.h>

namespace brewery {

class BeerService : public Service {
public:
    BeerService() = delete;
    explicit BeerService(Database& db);
    ~BeerService() override = default;

    void load(std::shared_ptr<Source>) override;
    void save(std::shared_ptr<Output>);
    std::vector<std::shared_ptr<Stock<Beer>>>& getAll();
    std::shared_ptr<Stock<Beer>> getStockByBeerName(const std::string&);
    std::shared_ptr<Stock<Beer>> getStockByIndex(int);
    void addStock(std::shared_ptr<Stock<Beer>>&);
    void deleteByName(const std::string&);

    BeerStockJson beerStockJson_;
private:
    Database db_;
};

} // namespace

#endif //BREWERY_MANAGEMENT_BEERSERVICE_H

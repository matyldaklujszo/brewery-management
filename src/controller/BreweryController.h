#ifndef BREWERY_MANAGEMENT_BREWERYCONTROLLER_H
#define BREWERY_MANAGEMENT_BREWERYCONTROLLER_H

#include <data/Database.h>
#include <data/BeerService.h>
#include <data/OrderService.h>

namespace brewery {

class BreweryController {
public:
    BreweryController() = delete;
    explicit BreweryController(const Config&, Database&);

    void loadAll();
    void saveAll();
    bool canOrderBeCompleted(int);
    std::vector<std::shared_ptr<Stock<Beer>>>& getAllBeerStocks();
    std::shared_ptr<Stock<Beer>> getStockByBeerName(const std::string&);
    std::vector<std::shared_ptr<Order>>& getAllOrders();
    std::shared_ptr<Order> getOrderById(int);
    void completeOrder(int);
    std::vector<std::string> getUniqueBeerNames();
    void addOrder(const std::shared_ptr<Order>&);
    void addBeerStock(std::shared_ptr<Stock<Beer>>);
    void deleteBeerStockByName(const std::string&);

private:
    Config config_;
    BeerService beerService_;
    OrderService orderService_;
};

}

#endif //BREWERY_MANAGEMENT_BREWERYCONTROLLER_H

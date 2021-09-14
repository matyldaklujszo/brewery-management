#ifndef BREWERY_MANAGEMENT_DATABASE_H
#define BREWERY_MANAGEMENT_DATABASE_H

#include <vector>

#include "models/Order.h"
#include "models/Stock.h"

namespace brewery {

class Database {
public:
    Database() = default;
    ~Database() = default;

    std::vector<std::shared_ptr<Order>> orders_;
    std::vector<std::shared_ptr<Stock<Beer>>> beerStocks_;
};

} // namespace

#endif //BREWERY_MANAGEMENT_DATABASE_H

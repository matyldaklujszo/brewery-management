#ifndef BREWERY_MANAGEMENT_ORDERSERVICE_H
#define BREWERY_MANAGEMENT_ORDERSERVICE_H

#include "Database.h"
#include "Service.h"
#include <utils/Config.h>
#include <json/OrderJson.h>
#include <file/Source.h>

namespace brewery {

class OrderService : public Service {
public:
    OrderService() = delete;
    explicit OrderService(Database& db);
    ~OrderService() override = default;

    void load(std::shared_ptr<Source>) override;
    void save(std::shared_ptr<Output>);
    std::shared_ptr<Order> getById(int);
    std::vector<std::shared_ptr<Order>>& getAll();
    void addOrder(const std::shared_ptr<Order>& sharedPtr);

    OrderJson orderJson_;

    private:
    Database db_;
};

} // namespace
#endif //BREWERY_MANAGEMENT_ORDERSERVICE_H

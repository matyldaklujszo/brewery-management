#ifndef BREWERY_MANAGEMENT_ORDER_H
#define BREWERY_MANAGEMENT_ORDER_H

#include <vector>
#include <ctime>
#include <optional>
#include <memory>

#include "Beer.h"
#include "Stock.h"
#include "Customer.h"

namespace brewery {

class Order {
public:
    using OrderList = std::vector<ProductQuantityPair<Beer>>;
    friend class OrderService;

    Order();
    ~Order() = default;

    std::string getOrderDate() const;
    bool isCompleted() const;
    std::string getCompletionDate() const;
    Customer getCustomer() const;
    OrderList getOrderedProducts() const;
    int getId() const;
    void complete();

    class OrderBuilder
    {
    public:
        OrderBuilder();
        explicit OrderBuilder(const std::shared_ptr<Order>&);
        explicit OrderBuilder(Order&);
        ~OrderBuilder() = default;
        operator Order() const;
        operator std::shared_ptr<Order>() const;

        OrderBuilder& placed(const std::string&);
        OrderBuilder& placed();
        OrderBuilder& completed(const std::string&);
        OrderBuilder& products(OrderList);
        OrderBuilder& product(ProductQuantityPair<Beer>);
        OrderBuilder& by(const Customer&);

    private:
        std::unique_ptr<Order> order_;
    };

private:
    static int getNextIndex();
    int id;
    OrderList beerList_;
    Customer customer_;
    std::string orderDate_;
    std::optional<std::string> completionDate_;

public:
    static OrderBuilder create();
    static OrderBuilder update(std::shared_ptr<Order>);
    static OrderBuilder update(Order&);
};

} //namespace

#endif //BREWERY_MANAGEMENT_ORDER_H

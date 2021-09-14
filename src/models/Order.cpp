#include <memory>
#include <iomanip>
#include <iostream>
#include <utility>
#include <utils/Time.h>
#include "Order.h"

using namespace brewery;

Order::OrderBuilder
Order::create()
{
    return {};
}

std::string
Order::getOrderDate() const
{
    return orderDate_;
}

std::string
Order::getCompletionDate() const
{
    return completionDate_.value();
}

Order::OrderBuilder
Order::update(std::shared_ptr<Order> order)
{
    return Order::OrderBuilder(order);
}

Order::OrderBuilder
Order::update(Order& order)
{
    return Order::OrderBuilder(order);
}

bool
Order::isCompleted() const
{
    return std::nullopt != completionDate_;
}

Customer
Order::getCustomer() const
{
    return customer_;
}

Order::OrderList
Order::getOrderedProducts() const
{
    return beerList_;
}

void
Order::complete()
{
    completionDate_ = getCurrentTime();
}

int
Order::getId() const
{
    return id;
}

int
Order::getNextIndex()
{
    static int id = 0;
    return id++;
}

Order::Order()
{
    id = Order::getNextIndex();
}

Order::OrderBuilder::OrderBuilder() :
    order_(std::make_unique<Order>())
{}


Order::OrderBuilder::OrderBuilder(Order& order) :
    order_(std::make_unique<Order>(order))
{}

Order::OrderBuilder::operator Order() const
{
    return *order_;
}

Order::OrderBuilder::operator std::shared_ptr<Order>() const
{
    return std::make_shared<Order>(*order_);
}

Order::OrderBuilder::OrderBuilder(const std::shared_ptr<Order>& order) :
    order_(std::make_unique<Order>(*order))
{}

Order::OrderBuilder&
Order::OrderBuilder::placed(const std::string& date)
{
    order_->orderDate_ = date;
    return *this;
}

Order::OrderBuilder&
Order::OrderBuilder::completed(const std::string& date)
{
    if (not date.empty())
    {
        order_->completionDate_ = date;
    }
    return *this;
}

Order::OrderBuilder&
Order::OrderBuilder::products(OrderList orderList)
{
    order_->beerList_ = std::move(orderList);
    return *this;
}

Order::OrderBuilder&
Order::OrderBuilder::by(const Customer& customer)
{
    order_->customer_ = customer;
    return *this;
}

Order::OrderBuilder&
Order::OrderBuilder::product(ProductQuantityPair<Beer> product)
{
    order_->beerList_.push_back(product);
    return *this;
}

Order::OrderBuilder&
Order::OrderBuilder::placed()
{
    this->placed(getCurrentTime());
    return *this;
}

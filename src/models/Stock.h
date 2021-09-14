#ifndef BREWERY_MANAGEMENT_STOCK_H
#define BREWERY_MANAGEMENT_STOCK_H

#include "ProductQuantityPair.h"
#include <stdlib.h>

namespace brewery {

template <class Model>
class Stock {
public:
    Stock() = delete;
    Stock(const Model& product, int quantity, double singularPrice) :
            item_(product, quantity),
            singularPrice_(singularPrice)
    {}
    ~Stock() = default;

    int getQuantity() const
    {
        return item_.quantity_;
    }

    Model getProduct() const
    {
        return item_.product_;
    }

    double getSingularPrice() const
    {
        return singularPrice_;
    }

    void setPrice(double price)
    {
        singularPrice_ = price;
    }

    void add(const int n)
    {
        item_.quantity_ += n;
    }

    void subtract(int n)
    {
        n = std::abs(n);
        if (item_.quantity_ - n >= 0)
        {
            item_.quantity_ -= n;
        }
        else
        {
            // TODO...
            item_.quantity_ = 0;
        }
    }
private:
    ProductQuantityPair<Model> item_;
    double singularPrice_;
};
}
#endif //BREWERY_MANAGEMENT_STOCK_H

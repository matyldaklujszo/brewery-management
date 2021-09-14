#ifndef BREWERY_MANAGEMENT_PRODUCTQUANTITYPAIR_H
#define BREWERY_MANAGEMENT_PRODUCTQUANTITYPAIR_H

namespace brewery {

template <class Model>
class ProductQuantityPair
{
public:
    ProductQuantityPair() = delete;
    ProductQuantityPair(const Model& product, int quantity) :
        product_(product),
        quantity_(quantity)
    {}

    Model product_;
    int quantity_;
};
}

#endif //BREWERY_MANAGEMENT_PRODUCTQUANTITYPAIR_H

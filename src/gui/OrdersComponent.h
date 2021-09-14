#ifndef BREWERY_MANAGEMENT_ORDERSCOMPONENT_H
#define BREWERY_MANAGEMENT_ORDERSCOMPONENT_H

#include <ftxui/component/component.hpp>
#include <controller/BreweryController.h>
#include "OrderDetailsModal.h"

namespace brewery {
class OrdersComponent : public ftxui::ComponentBase
{
public:
    OrdersComponent(std::shared_ptr<BreweryController>&);

    ftxui::Element Render() override;
    bool OnEvent(ftxui::Event) override;
    bool Focusable() const override { return true; }
private:
    std::shared_ptr<BreweryController> breweryController_;
    int selected_ = 0;
    int size_ = 0;
    bool openModal_ = false;
    std::shared_ptr<OrderDetailsModal> modal_;
};
}

#endif //BREWERY_MANAGEMENT_ORDERSCOMPONENT_H

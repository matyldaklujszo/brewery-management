#ifndef BREWERY_MANAGEMENT_ORDERDETAILSMODAL_H
#define BREWERY_MANAGEMENT_ORDERDETAILSMODAL_H

#include <models/Order.h>
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/component.hpp>
#include <controller/BreweryController.h>

namespace brewery {
class OrderDetailsModal : public ftxui::ComponentBase
{
public:
    OrderDetailsModal() = delete;
    explicit OrderDetailsModal(std::shared_ptr<BreweryController>, bool&);
    ftxui::Element Render(int);
    bool OnEvent(ftxui::Event) override;
    bool Focusable() const override { return true; }
private:
    ftxui::Component container_ = ftxui::Container::Vertical({});
    std::shared_ptr<ComponentBase> completeButton_;
    std::shared_ptr<BreweryController> controller_;
    int id_;
};
}

#endif //BREWERY_MANAGEMENT_ORDERDETAILSMODAL_H

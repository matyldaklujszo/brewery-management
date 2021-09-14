#ifndef BREWERY_MANAGEMENT_MAINCOMPONENT_H
#define BREWERY_MANAGEMENT_MAINCOMPONENT_H

#include <ftxui/component/component.hpp>
#include "ftxui/component/screen_interactive.hpp"
#include "BeerStockComponent.h"
#include "OrdersComponent.h"
#include "AddOrderComponent.h"
#include <controller/BreweryController.h>

namespace brewery {
class MainComponent : public ftxui::ComponentBase
{
public:
    MainComponent() = delete;
    explicit MainComponent(ftxui::ScreenInteractive&, std::shared_ptr<BreweryController>);
    ftxui::Element Render() override;
    bool OnEvent(ftxui::Event) override;
private:
    ftxui::ScreenInteractive& screen_;
    std::shared_ptr<BreweryController> breweryController_;
    int selectedTab_ = 0;
    std::vector<std::wstring> tabNames_ = {
            L"Beer Stock",
            L"Orders",
            L"Add order"
    };
    ftxui::Component toggle_ = ftxui::Toggle(&tabNames_, &selectedTab_);
    ftxui::Component footer_ = ftxui::Container::Horizontal({});
    std::shared_ptr<BeerStockComponent> beerStockComponent_ = ftxui::Make<BeerStockComponent>(breweryController_);
    std::shared_ptr<OrdersComponent> ordersComponent_ = ftxui::Make<OrdersComponent>(breweryController_);
    std::shared_ptr<AddOrderComponent> addOrderComponent_ = ftxui::Make<AddOrderComponent>(breweryController_);
};
}

#endif //BREWERY_MANAGEMENT_MAINCOMPONENT_H

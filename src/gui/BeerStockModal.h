#ifndef BREWERY_MANAGEMENT_BEERSTOCKMODAL_H
#define BREWERY_MANAGEMENT_BEERSTOCKMODAL_H

#include <ftxui/component/component.hpp>
#include <models/Beer.h>
#include <models/Stock.h>
#include <controller/BreweryController.h>

namespace brewery {
class BeerStockModal : public ftxui::ComponentBase
{
public:
    BeerStockModal(std::shared_ptr<BreweryController>&, bool&);
    ftxui::Element Render(std::shared_ptr<Stock<Beer>>);
    bool OnEvent(ftxui::Event) override;
    bool Focusable() const override { return true; }
private:
    std::shared_ptr<ComponentBase> closeButton_;
    std::shared_ptr<ComponentBase> deleteButton_;
    std::shared_ptr<ComponentBase> quantityInput_;
    std::shared_ptr<ComponentBase> priceInput_;
    std::string quantityModifyStr_;
    std::string priceModifyStr_;
    std::shared_ptr<Stock<Beer>> stock_;
    std::shared_ptr<BreweryController> controller_;
};
}

#endif //BREWERY_MANAGEMENT_BEERSTOCKMODAL_H

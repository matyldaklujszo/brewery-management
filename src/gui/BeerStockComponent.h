#ifndef BREWERY_MANAGEMENT_BEERSTOCKCOMPONENT_H
#define BREWERY_MANAGEMENT_BEERSTOCKCOMPONENT_H

#include <ftxui/component/component.hpp>
#include <controller/BreweryController.h>
#include "BeerStockModal.h"
#include "AddStockModal.h"

namespace brewery {
class BeerStockComponent : public ftxui::ComponentBase
{
public:
    using BeerStock = Stock<Beer>;
    explicit BeerStockComponent(std::shared_ptr<BreweryController>&);

    ftxui::Element Render() override;
    bool OnEvent(ftxui::Event) override;
    bool Focusable() const override { return true; }
private:
    std::shared_ptr<BreweryController> breweryController_;
    std::shared_ptr<ftxui::ComponentBase> addStockButton_;
    int selected_ = 0;
    int size_ = 0;
    bool openDetailsModal_ = false;
    bool openNewStockModal_ = false;
    std::shared_ptr<BeerStockModal> detailsModal_;
    std::shared_ptr<AddStockModal> addStockModal_;
};
}

#endif //BREWERY_MANAGEMENT_BEERSTOCKCOMPONENT_H

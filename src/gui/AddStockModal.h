#ifndef BREWERY_MANAGEMENT_ADDSTOCKMODAL_H
#define BREWERY_MANAGEMENT_ADDSTOCKMODAL_H


#include <ftxui/component/component_base.hpp>
#include <controller/BreweryController.h>

namespace brewery {
class AddStockModal : public ftxui::ComponentBase
{
public:
    explicit AddStockModal(std::shared_ptr<BreweryController>&, bool&);
    ftxui::Element Render() override;
    bool OnEvent(ftxui::Event) override;
    bool Focusable() const override { return true; }
private:
    std::shared_ptr<BreweryController> controller_;
    std::shared_ptr<ComponentBase> submitButton_;
    std::shared_ptr<ComponentBase> closeButton_;
    std::shared_ptr<ComponentBase> nameInput_;
    std::shared_ptr<ComponentBase> quantityInput_;
    std::shared_ptr<ComponentBase> priceInput_;
    std::string nameStr_;
    std::string quantityStr_;
    std::string priceStr_;
};
}


#endif //BREWERY_MANAGEMENT_ADDSTOCKMODAL_H

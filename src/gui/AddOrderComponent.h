#ifndef BREWERY_MANAGEMENT_ADDORDERCOMPONENT_H
#define BREWERY_MANAGEMENT_ADDORDERCOMPONENT_H

#include <ftxui/component/component_base.hpp>
#include <controller/BreweryController.h>

namespace brewery {
class AddOrderComponent : public ftxui::ComponentBase
{
public:
    explicit AddOrderComponent(std::shared_ptr<BreweryController>&);
    ftxui::Element Render() override;
    bool OnEvent(ftxui::Event) override;
private:
    std::shared_ptr<BreweryController> breweryController_;
    std::shared_ptr<ftxui::ComponentBase> beerNameRadiobox_;
    std::shared_ptr<ComponentBase> quantityInput_;
    std::string quantityStr_;
    std::shared_ptr<ComponentBase> companyInput_;
    std::string companyStr_;
    std::shared_ptr<ComponentBase> submitButton_;
    int chosenBeer_;
    std::vector<std::string> uniqueBeerNames_;
    Order order_;
};
}

#endif //BREWERY_MANAGEMENT_ADDORDERCOMPONENT_H

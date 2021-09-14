#include <ftxui/component/event.hpp>
#include <ftxui/component/component.hpp>
#include "AddOrderComponent.h"

using namespace brewery;

AddOrderComponent::AddOrderComponent(std::shared_ptr<BreweryController>& controller) :
    breweryController_(controller)
{
    uniqueBeerNames_ = breweryController_->getUniqueBeerNames();
    beerNameRadiobox_ = ftxui::Radiobox(&uniqueBeerNames_, &chosenBeer_);
    auto inputOption = ftxui::InputOption();
    inputOption.on_enter = [&] {
        Beer beer{uniqueBeerNames_[chosenBeer_]};
        // TODO throw
        int quantity = std::stoi(quantityStr_, nullptr, 10);
        order_ = Order::update(order_).product({beer, quantity});
        quantityStr_ = "";
    };
    quantityInput_ = ftxui::Input(&quantityStr_, L"", inputOption);
    companyInput_ = ftxui::Input(&companyStr_, L"Company name");
    submitButton_ = ftxui::Button(L"Submit", [&] {
        order_ = Order::update(order_).placed().by(Customer(companyStr_));
        breweryController_->addOrder(std::make_shared<Order>(order_));
        order_ = Order();
        quantityStr_.clear();
        companyStr_.clear();
    });

    Add(ftxui::Container::Vertical({
        beerNameRadiobox_,
        quantityInput_,
        companyInput_,
        submitButton_
    }));
}

ftxui::Element
AddOrderComponent::Render()
{
    uniqueBeerNames_ = breweryController_->getUniqueBeerNames();
    auto header = ftxui::hbox({
        ftxui::text(L"Name") | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 20) | ftxui::notflex,
        ftxui::separator(),
        ftxui::text(L"Quantity") | ftxui::flex_shrink,
    });

    ftxui::Elements orderedItems;
    for (auto& orderItem : order_.getOrderedProducts())
    {
        ftxui::Element record = ftxui::hbox({
            ftxui::text(orderItem.product_.getName()) | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 20) | ftxui::notflex,
            ftxui::separator(),
            ftxui::text(std::to_string(orderItem.quantity_)) | ftxui::flex_shrink,
        }) | ftxui::flex;
        orderedItems.push_back(record);
    }

    return ftxui::window(ftxui::text(L"New order"), ftxui::vbox({
        ftxui::window(ftxui::text(L"Beer"), beerNameRadiobox_->Render()),
        ftxui::window(ftxui::text(L"Quantity"), quantityInput_->Render()),
        ftxui::window(ftxui::text(L"Company"), companyInput_->Render()),
        ftxui::hbox({
            ftxui::window(ftxui::text(L"Summary"), ftxui::vbox({
                header,
                ftxui::separator(),
                ftxui::vbox(orderedItems)})),
            submitButton_->Render() | ftxui::align_right
        })
    }));
}

bool
AddOrderComponent::OnEvent(ftxui::Event event)
{
    return ComponentBase::OnEvent(event);
}

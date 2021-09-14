#include <ftxui/component/event.hpp>
#include <ftxui/component/component.hpp>
#include "AddStockModal.h"

using namespace brewery;

AddStockModal::AddStockModal(std::shared_ptr<BreweryController>& controller, bool& openModal) :
    controller_(controller)
{
    nameInput_ = ftxui::Input(&nameStr_, L"Beer name");
    quantityInput_ = ftxui::Input(&quantityStr_, L"Quantity");
    priceInput_ = ftxui::Input(&priceStr_, L"Price");

    closeButton_ = ftxui::Button(L"Close", [&] {
       openModal = false;
    });
    submitButton_ = ftxui::Button(L"Submit", [&] {
        // TODO test
        int quantityNumber = std::stoi(quantityStr_, nullptr, 10);
        double priceNumber = std::stod(priceStr_, nullptr);

        Beer beer{nameStr_};
        controller_->addBeerStock(std::make_shared<Stock<Beer>>(beer, quantityNumber, priceNumber));
        openModal = false;
    });
    Add(ftxui::Container::Vertical({
        nameInput_,
        quantityInput_,
        priceInput_,
        ftxui::Container::Horizontal({
            submitButton_,
            closeButton_
        })
    }));
}

ftxui::Element
AddStockModal::Render()
{
    return ftxui::window(ftxui::text(L"Add stock"), ftxui::vbox({
        nameInput_->Render(),
        quantityInput_->Render(),
        priceInput_->Render(),
        ftxui::hbox({
            submitButton_->Render(),
            closeButton_->Render()
        })
    }));
}

bool
AddStockModal::OnEvent(ftxui::Event event)
{
    ComponentBase::OnEvent(event);
    return true;
}

#include <ftxui/component/event.hpp>
#include <logging/LogHelpers.h>
#include <iomanip>
#include "BeerStockModal.h"

using namespace brewery;

BeerStockModal::BeerStockModal(std::shared_ptr<BreweryController>& controller, bool& openModal) :
    controller_(controller)
{
    auto inputOption = ftxui::InputOption();
    inputOption.on_enter = [&] {
        // TODO throw
        if (!quantityModifyStr_.empty())
        {
            int quantityModifyNumber = std::stoi(quantityModifyStr_, nullptr, 10);
            LOG_INFO("Update " << stock_->getProduct().getName() << " stock quantity by " << quantityModifyNumber);
            if (quantityModifyNumber < 0)
            {
                stock_->subtract(quantityModifyNumber);
            }
            else
            {
                stock_->add(quantityModifyNumber);
            }
        }
    };
    quantityInput_ = ftxui::Input(&quantityModifyStr_, L"Quantity", inputOption);

    inputOption.on_enter = [&] {
        if (!priceModifyStr_.empty())
        {
            // TODO throw
            double priceModifyNumber = std::stod(priceModifyStr_, nullptr);
            LOG_INFO("Update " << stock_->getProduct().getName() << " price to " << priceModifyNumber);
            stock_->setPrice(priceModifyNumber);
        }
    };
    priceInput_ = ftxui::Input(&priceModifyStr_, L"Price", inputOption);

    closeButton_ = ftxui::Button(L"Close", [&] {
        openModal = false;
        quantityModifyStr_.clear();
        priceModifyStr_.clear();
    });

    deleteButton_ = ftxui::Button(L"Delete", [&] {
        openModal = false;
        controller_->deleteBeerStockByName(stock_->getProduct().getName());
    });

    Add(ftxui::Container::Vertical({
        quantityInput_,
        priceInput_,
//        ftxui::Container::Horizontal({
//            deleteButton_,
            closeButton_
//        })
    }));
}

bool
BeerStockModal::OnEvent(ftxui::Event event)
{
    ComponentBase::OnEvent(event);
    return true;
}

ftxui::Element
BeerStockModal::Render(std::shared_ptr<Stock<Beer>> stock)
{
    stock_ = stock;

    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << stock->getSingularPrice();

    return ftxui::window(ftxui::text(L"Stock"), ftxui::vbox({
        ftxui::text("Beer: " + stock_->getProduct().getName()),
        ftxui::text("Quantity: " + std::to_string(stock_->getQuantity())),
        ftxui::text("Price: " + ss.str()),
        ftxui::window(ftxui::text(L"Update"), ftxui::vbox({
            quantityInput_->Render(),
            priceInput_->Render()
        })),
//        ftxui::hbox({
//            deleteButton_->Render(),
            closeButton_->Render()
//        })
    }));
}

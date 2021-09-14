#include <ftxui/component/event.hpp>
#include <sstream>
#include <iomanip>
#include <logging/LogHelpers.h>
#include "BeerStockComponent.h"
#include "BeerStockModal.h"

using namespace brewery;

BeerStockComponent::BeerStockComponent(std::shared_ptr<BreweryController>& controller) :
    breweryController_(controller),
    detailsModal_(ftxui::Make<BeerStockModal>(breweryController_, openDetailsModal_)),
    addStockModal_(ftxui::Make<AddStockModal>(breweryController_, openNewStockModal_))
{
    addStockButton_ = ftxui::Button(L"Add stock", [&] {
        openNewStockModal_ = true;
    });
    Add({ftxui::Container::Vertical({
        ftxui::Container::Vertical({}),
        addStockButton_}),
    });
}

bool
BeerStockComponent::OnEvent(ftxui::Event event)
{
    if (openDetailsModal_)
    {
        return detailsModal_->OnEvent(event);
    }

    if (openNewStockModal_)
    {
        return addStockModal_->OnEvent(event);
    }

    int oldSelected = selected_;
    if (event == ftxui::Event::ArrowUp || event == ftxui::Event::Character('k'))
    {
        selected_--;
    }
    if (event == ftxui::Event::ArrowDown || event == ftxui::Event::Character('j'))
    {
        selected_++;
    }

    if (selected_ == size_)
    {
        return ftxui::ComponentBase::OnEvent(event);
    }
    else
    {
        if (event == ftxui::Event::Return || event == ftxui::Event::Character(' '))
        {
            openDetailsModal_ = true;
        }
    }

    selected_ = std::max(0, std::min(size_, selected_));

    return selected_ != oldSelected;
}

ftxui::Element
BeerStockComponent::Render()
{
    auto beerStocks = breweryController_->getAllBeerStocks();
    size_ = beerStocks.size();

    auto header = ftxui::hbox({
        ftxui::text(L"Name") | ftxui::flex,
        ftxui::separator(),
        ftxui::text(L"Quantity") | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 20) | ftxui::notflex,
        ftxui::separator(),
        ftxui::text(L"Singular price") | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 20) | ftxui::notflex
    });

    int idx = 0;
    ftxui::Elements records;
    for (auto& stock : beerStocks)
    {
        ftxui::Decorator decorator = ftxui::dim;
        if (selected_ == idx++)
        {
            decorator = decorator | ftxui::focus | ftxui::inverted;
        }
        std::stringstream ss;
        ss << std::fixed << std::setprecision(2) << stock->getSingularPrice();

        ftxui::Element record = ftxui::hbox({
            ftxui::text(stock->getProduct().getName()) | ftxui::flex,
            ftxui::separator(),
            ftxui::text(std::to_string(stock->getQuantity())) | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 20) | ftxui::notflex,
            ftxui::separator(),
            ftxui::text(ss.str()) | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 20) | ftxui::notflex
        }) | ftxui::flex | decorator;
        records.push_back(record);
    }

    auto window = ftxui::window(ftxui::text(L"Beer Stock"),ftxui::vbox({
        header,
        ftxui::separator(),
        ftxui::vbox(records) | ftxui::yframe,
        ftxui::filler(),
        addStockButton_->Render() | ftxui::align_right | ftxui::size(ftxui::HEIGHT, ftxui::LESS_THAN, 3)
    }));

    if (openDetailsModal_)
    {
        LOG_INFO("Opening stock #" << selected_ << " details");
        window = ftxui::dbox(window,
                             detailsModal_->Render(beerStocks[selected_]) | ftxui::clear_under | ftxui::center);
    }

    if (openNewStockModal_)
    {
        window = ftxui::dbox(window,
                             addStockModal_->Render() | ftxui::clear_under | ftxui::center);
    }

    return window;
}



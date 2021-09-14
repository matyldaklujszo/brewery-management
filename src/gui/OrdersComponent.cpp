#include <ftxui/component/event.hpp>
#include "OrdersComponent.h"
#include <logging/LogHelpers.h>
#include <iomanip>

using namespace brewery;

OrdersComponent::OrdersComponent(std::shared_ptr<BreweryController>& controller) :
    breweryController_(controller),
    modal_(ftxui::Make<OrderDetailsModal>(breweryController_, openModal_))
{}

bool
OrdersComponent::OnEvent(ftxui::Event event)
{
    if (openModal_)
    {
        return modal_->OnEvent(event);
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
    if (event == ftxui::Event::Return || event == ftxui::Event::Character(' '))
    {
        openModal_ = true;
    }
//    LOG_INFO("SELECTED " << selected_);
    selected_ = std::max(0, std::min(size_ - 1, selected_));

    return oldSelected != selected_;
}

ftxui::Element
brewery::OrdersComponent::Render()
{
    auto orders = breweryController_->getAllOrders();
    size_ = orders.size();

    auto header = ftxui::hbox({
        ftxui::text(L"Id") | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 10) | ftxui::notflex,
        ftxui::separator(),
        ftxui::text(L"Customer") | ftxui::flex,
        ftxui::separator(),
        ftxui::text(L"Value") | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 20) | ftxui::notflex,
        ftxui::separator(),
        ftxui::text(L"Order date") | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 30) | ftxui::notflex,
        ftxui::separator(),
        ftxui::text(L"Completion date") | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 30) | ftxui::notflex,
    });

    int idx = 0;
    ftxui::Elements records;
    for (auto& order : orders)
    {

        auto completionDate = order->isCompleted() ? order->getCompletionDate() : "Not completed";

        ftxui::Decorator completionDecorator;
        if (order->isCompleted())
        {
            completionDecorator = ftxui::nothing;
        }
        else if (breweryController_->canOrderBeCompleted(idx))
        {
            completionDecorator = ftxui::color(ftxui::Color::Green);
        }
        else
        {
            completionDecorator = ftxui::color(ftxui::Color::Red);
        }

        ftxui::Decorator lineDecorator = ftxui::dim;
        if (selected_ == idx++)
        {
            lineDecorator = lineDecorator | ftxui::focus | ftxui::inverted;
        }

        double orderValue = 0;
        for (auto& orderItem : order->getOrderedProducts())
        {
            double singularBeerPrice = breweryController_->getStockByBeerName(orderItem.product_.getName())->getSingularPrice();
            orderValue += singularBeerPrice * orderItem.quantity_;
        }

        std::stringstream ss;
        ss << std::fixed << std::setprecision(2) << orderValue;

        ftxui::Element record = ftxui::hbox({
            ftxui::text(std::to_string(order->getId())) | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 10) | ftxui::notflex,
            ftxui::separator(),
            ftxui::text(order->getCustomer().getName()) | ftxui::flex,
            ftxui::separator(),
            ftxui::text(ss.str()) | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 20) | ftxui::notflex,
            ftxui::separator(),
            ftxui::text(order->getOrderDate()) | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 30) | ftxui::notflex,
            ftxui::separator(),
            ftxui::text(completionDate) | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 30) | ftxui::notflex | completionDecorator,
        }) | ftxui::flex | lineDecorator;
        records.push_back(record);
    }

    auto window = ftxui::window(ftxui::text(L"Orders"),ftxui::vbox({
        header,
        ftxui::separator(),
        ftxui::vbox(records) | ftxui::yframe
    }));

    if (openModal_)
    {
        window = ftxui::dbox(window,
                             modal_->Render(selected_) | ftxui::clear_under | ftxui::center);
    }

    return window;

}

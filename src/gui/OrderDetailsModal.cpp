#include <ftxui/component/event.hpp>
#include <logging/LogHelpers.h>
#include "OrderDetailsModal.h"

using namespace brewery;

OrderDetailsModal::OrderDetailsModal(std::shared_ptr<BreweryController> controller, bool& openModal) :
    controller_(controller)
{
    completeButton_ = ftxui::Button(L"Complete", [&] {
        controller_->completeOrder(id_);
        LOG_INFO("Order #" << id_ << " completed");
    });
    container_->Add(ftxui::Button(L"Close", [&] { openModal = false; }));
    Add(ftxui::Container::Vertical({
        completeButton_,
        container_
    }));
}

ftxui::Element
OrderDetailsModal::Render(int id)
{
    id_ = id;
    auto order = controller_->getOrderById(id_);

    auto header = ftxui::hbox({
        ftxui::text(L"Name") | ftxui::flex,
        ftxui::separator(),
        ftxui::text(L"Quantity") | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 20) | ftxui::notflex,
    });

    ftxui::Elements records;
    for (auto& orderItem : order->getOrderedProducts())
    {
        ftxui::Element record = ftxui::hbox({
            ftxui::text(orderItem.product_.getName()) | ftxui::flex,
            ftxui::separator(),
            ftxui::text(std::to_string(orderItem.quantity_)) | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 20) | ftxui::notflex,
        }) | ftxui::flex;
        records.push_back(record);
    }
    records.push_back(ftxui::separator());

    if (controller_->canOrderBeCompleted(id_))
    {
        return ftxui::window(ftxui::text(L"Order"), ftxui::vbox({
            header,
            ftxui::separator(),
            ftxui::vbox(records),
            ftxui::filler() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 5),
            completeButton_->Render() | ftxui::size(ftxui::HEIGHT, ftxui::LESS_THAN, 15),
            container_->Render() | ftxui::size(ftxui::HEIGHT, ftxui::LESS_THAN, 15)
        }));
    }

    return ftxui::window(ftxui::text(L"Order"), ftxui::vbox({
        header,
        ftxui::separator(),
        ftxui::vbox(records),
        ftxui::filler() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 5),
        container_->Render() | ftxui::size(ftxui::HEIGHT, ftxui::LESS_THAN, 15)
    }));
}

bool
OrderDetailsModal::OnEvent(ftxui::Event event)
{
    ComponentBase::OnEvent(event);
    return true;
}

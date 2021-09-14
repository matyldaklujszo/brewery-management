#include <logging/LogHelpers.h>
#include <ftxui/component/event.hpp>
#include "MainComponent.h"

using namespace brewery;

MainComponent::MainComponent(ftxui::ScreenInteractive& screen, std::shared_ptr<BreweryController> breweryController) :
    screen_(screen),
    breweryController_(breweryController)
{
    footer_->Add(ftxui::Button("Save", [&] {
        breweryController_->saveAll();
    }));
    footer_->Add(ftxui::Button("Quit", [&] {
        LOG_INFO("Exiting app...");
        screen_.ExitLoopClosure()();
    }));

    Add(ftxui::Container::Vertical({
            toggle_,
            ftxui::Container::Tab({
                beerStockComponent_,
                ordersComponent_,
                addOrderComponent_
            }, &selectedTab_),
            footer_
        })
    );
}

ftxui::Element
MainComponent::Render()
{
    auto time = getCurrentTime();
    auto header = ftxui::hbox({
        ftxui::text(L"brewery-management"),
        ftxui::hcenter(toggle_->Render()),
        ftxui::text(std::wstring(time.begin(), time.end()))
    });

    if (selectedTab_ == 0)
    {
        return ftxui::vbox({
            header,
            ftxui::separator(),
            beerStockComponent_->Render() | ftxui::size(ftxui::HEIGHT, ftxui::GREATER_THAN, 15),
            ftxui::filler(),
            footer_->Render() | ftxui::align_right | ftxui::size(ftxui::HEIGHT, ftxui::LESS_THAN, 3)
        });
    }

    if (selectedTab_ == 1)
    {
        return ftxui::vbox({
            header,
            ftxui::separator(),
            ordersComponent_->Render() | ftxui::size(ftxui::HEIGHT, ftxui::GREATER_THAN, 15),
            ftxui::filler(),
            footer_->Render() | ftxui::align_right | ftxui::size(ftxui::HEIGHT, ftxui::LESS_THAN, 3)
        });
    }

    if (selectedTab_ == 2)
    {
        return ftxui::vbox({
            header,
            ftxui::separator(),
            addOrderComponent_->Render() | ftxui::size(ftxui::HEIGHT, ftxui::GREATER_THAN, 15),
            ftxui::filler(),
            footer_->Render() | ftxui::align_right | ftxui::size(ftxui::HEIGHT, ftxui::LESS_THAN, 3)
        });
    }

    return ftxui::vbox({
        header,
        ftxui::separator(),
        ftxui::text(L"ORDERS"),
        ftxui::filler(),
        footer_->Render() | ftxui::align_right | ftxui::size(ftxui::HEIGHT, ftxui::LESS_THAN, 15)
    });
}

bool
MainComponent::OnEvent(ftxui::Event event)
{
    return ComponentBase::OnEvent(event);
}

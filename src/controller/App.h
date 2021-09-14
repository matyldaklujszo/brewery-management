#ifndef BREWERY_MANAGEMENT_APP_H
#define BREWERY_MANAGEMENT_APP_H

#include <data/Database.h>
#include "BreweryController.h"
#include "ftxui/component/screen_interactive.hpp"

namespace brewery {
class App
{
public:
    App() = delete;
    explicit App(Config&);
    ~App() = default;

    void run();
private:
    Database db_;
    std::shared_ptr<BreweryController> controller_;
    ftxui::ScreenInteractive screen_ = ftxui::ScreenInteractive::Fullscreen();
};
}

#endif //BREWERY_MANAGEMENT_APP_H

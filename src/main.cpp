#include <iostream>

#include <file/FileOutput.h>
#include <logging/Logger.h>
#include <logging/LogHelpers.h>
#include <controller/App.h>
#include <utils/ConfigLoader.h>

#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/component_options.hpp"
#include "ftxui/component/event.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/color.hpp"
using namespace ftxui;
using namespace brewery;

int main() {
    auto config = ConfigLoader::load();
    Logger::setOutput(std::make_unique<FileOutput>(config.getLogPath(), true));
    if (config.isSetLogLevel())
    {
        Logger::setLogLevel(config.getLogLevel());
    }
    LOG_INFO("Logger set to " << config.getLogPath() << " with logLevel=" << Logger::getLogLevel());

    App app{config};
    app.run();

    return 0;
}

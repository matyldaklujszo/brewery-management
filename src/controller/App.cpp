#include <file/FileSource.h>
#include <file/FileOutput.h>
#include <json/ConfigJson.h>
#include <logging/Logger.h>
#include <logging/LogHelpers.h>
#include <gui/MainComponent.h>
#include "App.h"

using namespace brewery;

App::App(Config& cfg)
{
    controller_ = std::make_shared<BreweryController>(cfg, db_);
}

void
App::run()
{
    LOG_INFO("App startup");
    controller_->loadAll();
    auto mainComponent = std::make_shared<MainComponent>(screen_, controller_);
    LOG_INFO("Starting main loop");
    screen_.Loop(mainComponent);
}

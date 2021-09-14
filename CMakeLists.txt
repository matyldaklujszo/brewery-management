cmake_minimum_required(VERSION 3.16)

#-------------
include(FetchContent)

set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(ftxui
        GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
        )

FetchContent_GetProperties(ftxui)
if (NOT ftxui_POPULATED)
    FetchContent_Populate(ftxui)
    add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
endif ()

FetchContent_Declare(rapidjson
        GIT_REPOSITORY https://github.com/Tencent/rapidjson
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        )

FetchContent_GetProperties(rapidjson)
if (NOT rapidjson_POPULATED)
    FetchContent_Populate(rapidjson)
    set(rapidjson_INCLUDE_DIR ${rapidjson_SOURCE_DIR}/include)
endif ()
#-------------

project(brewery-management)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-builtin-macro-redefined -D'__FILE__=\"$(subst $(realpath ${CMAKE_SOURCE_DIR})/,,$(abspath $<))\"'")

add_executable(brewery-management src/main.cpp src/data/Database.cpp src/data/Database.h src/models/Order.cpp src/models/Order.h src/models/Beer.cpp src/models/Beer.h src/data/OrderService.cpp src/data/OrderService.h src/data/BeerService.cpp src/data/BeerService.h src/file/Source.h src/file/FileSource.cpp src/file/FileSource.h src/data/Service.h src/utils/Config.cpp src/utils/Config.h src/json/ConfigJson.cpp src/json/ConfigJson.h src/utils/Constants.h src/json/Json.h src/json/Json.cpp src/models/Stock.h src/json/BeerStockJson.cpp src/json/BeerStockJson.h src/file/Output.h src/file/FileOutput.cpp src/file/FileOutput.h src/logging/Logger.cpp src/logging/Logger.h src/logging/LogHelpers.h src/controller/BreweryController.cpp src/controller/BreweryController.h src/json/OrderJson.cpp src/json/OrderJson.h src/controller/App.cpp src/controller/App.h src/utils/ConfigLoader.cpp src/utils/ConfigLoader.h src/models/Customer.cpp src/models/Customer.h src/utils/Time.h src/models/ProductQuantityPair.h src/gui/MainComponent.cpp src/gui/MainComponent.h src/gui/BeerStockComponent.cpp src/gui/BeerStockComponent.h src/gui/BeerStockModal.cpp src/gui/BeerStockModal.h src/gui/OrdersComponent.cpp src/gui/OrdersComponent.h src/gui/OrderDetailsModal.cpp src/gui/OrderDetailsModal.h src/gui/AddOrderComponent.cpp src/gui/AddOrderComponent.h src/gui/AddStockModal.cpp src/gui/AddStockModal.h)

target_include_directories(brewery-management
        PRIVATE src
        PRIVATE ${rapidjson_INCLUDE_DIR}
        )

target_link_libraries(brewery-management
        PRIVATE ftxui::screen
        PRIVATE ftxui::dom
        PRIVATE ftxui::component
        )

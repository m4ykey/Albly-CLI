#include "AlblyApp.h"
#include <iostream>

#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>

#include "ftxui/component/event.hpp"

using namespace ftxui;

AlblyApp::AlblyApp(std::function<void()> callback) : exitCallback(callback) { }

Component AlblyApp::Create() {
    container = Container::Tab(
        {
            RenderMenu(),
            RenderSearch()
        },
        &currentTab
    );

    return container;
}

Component AlblyApp::RenderMenu() {
    auto menu = Menu(
        &items,
        &selected
        );

    menu |= CatchEvent(
        [this](Event event) {
            if (event == Event::Return) {
                if (selected == 1) {
                    currentTab = 1;
                    return true;
                }

                if (selected == 2) {
                    exitCallback();
                    return true;
                }
            }

            return false;
        }
    );

    return Renderer(menu, [menu] {
            return vbox({
                text("Albly")
                    | bold
                    | center,

                separator(),

                menu->Render()

            }) | border;
    });
}

Component AlblyApp::RenderSearch() {
    return Renderer([] {
        return vbox({
        text("Search")
        | bold
        | center,

        separator(),
        text("Search View")
        }) | border;
    });
}

#include "AlblyApp.h"
#include <iostream>

#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>

#include "ftxui/component/event.hpp"

using namespace ftxui;

AlblyApp::AlblyApp(std::function<void()> callback) : exitCallback(callback) { }

Component AlblyApp::Create() {
    auto menu = RenderMenu();

    return menu | CatchEvent([](Event event) {
        return false;
    });
}

Component AlblyApp::RenderMenu() {
    auto menu = Menu(
        &items,
        &selected
        );

    menu |= CatchEvent(
        [this](Event event) {
            if (event == Event::Return) {
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
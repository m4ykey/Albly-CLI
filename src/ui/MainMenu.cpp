#include "MainMenu.h"

#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>

namespace ui {
    MainMenu::MainMenu(std::function<void()> callback)
        : onSearch(callback) {
        
    }

    ftxui::Component MainMenu::Create()
    {
        using namespace ftxui;

        auto menu = Menu(
            &entries,
            &selected
        );

        return Renderer(menu, [menu] {
            return vbox({
            text("Albly")
                | bold
                | center,
                separator(),
                menu->Render(),
                separator(),
                text("↑ ↓ Choose | Enter Select")
            })
            | border;
        });
    }
}
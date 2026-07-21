#pragma once

#include <vector>
#include <string>
#include <functional>

#include <ftxui/component/component.hpp>

namespace ui {
    class MainMenu {
    public:
        MainMenu(std::function<void()> callback);
        ftxui::Component Create();

    private:
        std::function<void()> onSearch;

        std::vector<std::string> entries {
            "Collection",
            "Search",
            "New Release",
            "Listen Later",
            "Settings",
            "Exit"
        };

        int selected = 0;
    };
}

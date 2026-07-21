#pragma once

#include <ftxui/component/component.hpp>
#include <vector>
#include <string>
#include <functional>

class AlblyApp {
public:
    AlblyApp(std::function<void()> exitCallback);

    ftxui::Component Create();

private:
    ftxui::Component RenderMenu();

    std::function<void()> exitCallback;

    std::vector<std::string> items {
        "Collection",
        "Search",
        "Exit"
    };

    int selected = 0;
};
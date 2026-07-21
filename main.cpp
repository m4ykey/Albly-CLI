#include <ftxui/ftxui.hpp>

using namespace ftxui;

int main() {
    auto screen = ScreenInteractive::TerminalOutput();

    std::vector<std::string> entries = {
        "Collection",
        "Search",
        "New Release",
        "Listen Later",
        "Settings"
    };

    int selected = 0;

    auto menu = Menu(&entries, &selected);

    auto renderer = Renderer(menu, [&] {
        return vbox({
            text("Albly") | bold | center,
            separator(),
            menu->Render(),
            separator(),
            text("↑ ↓ Choose | Enter Select")
        }) | border;
    });

    screen.Loop(renderer);

    return 0;
}
#include <ftxui/ftxui.hpp>

#include "src/app/AlblyApp.h"

using namespace ftxui;

int main() {
    using namespace ftxui;

    auto screen = ScreenInteractive::TerminalOutput();

    AlblyApp app([&] {
        screen.Exit();
    });

    auto component = app.Create();

    screen.Loop(component);

    return 0;
}
#include <ftxui/ftxui.hpp>
#include "src/app/App.h"

using namespace ftxui;

int main() {
    using namespace ftxui;

    auto screen = ScreenInteractive::TerminalOutput();

    app::App myApp([&] {
        screen.Exit();
    });

    auto component = myApp.Create();

    screen.Loop(component);

    return 0;
}
#include <ftxui/ftxui.hpp>
#include "src/app/App.h"
#include <windows.h>

using namespace ftxui;

int main() {
    SetConsoleTitle("Albly");

    using namespace ftxui;

    auto screen = ScreenInteractive::TerminalOutput();

    app::App myApp([&] {
        screen.Exit();
    });

    auto component = myApp.Create();

    screen.Loop(component);

    return 0;
}
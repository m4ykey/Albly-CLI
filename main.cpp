#include <ftxui/ftxui.hpp>

using namespace ftxui;

int main() {
    auto screen = ScreenInteractive::TerminalOutput();

    auto button = Button(
        "Exit",
        [&] {
            screen.Exit();
        }
    );

    screen.Loop(button);

    return 0;
}
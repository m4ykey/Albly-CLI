#include "SearchView.h"

#include <ftxui/dom/elements.hpp>

namespace ui {
    ftxui::Component SearchView::Create() {
        using namespace ftxui;

        return Renderer([] {
            return vbox({
            text("SEARCH")
            | bold
            | center,
            separator(),
            text("Tutaj będzie wyszukiwarka"),
            text("ESC - wróć")
            }) | border;
        });
    }
}

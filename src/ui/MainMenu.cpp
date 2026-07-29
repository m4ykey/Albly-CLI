#include "MainMenu.h"

#include <ftxui/component/event.hpp>
#include <ftxui/dom/elements.hpp>

namespace ui {
	MainMenu::MainMenu(std::function<void(int)> onSelect)
		: onSelect(std::move(onSelect)) {  }

	ftxui::Component MainMenu::Create() {
		using namespace ftxui;

		auto onSelectCopy = onSelect;

		auto menu = Menu(&entries, &selected);

		menu |= CatchEvent([onSelectCopy, this](Event event) {
			if (event == Event::Return)
			{
				onSelectCopy(selected);
				return true;
			}
			return false;
		});

		return Renderer(menu, [menu] {
			return vbox({
				text("Albly") | bold | center,
				separator(),
				menu->Render(),
				separator(),
				text("↑ ↓ Choose | Enter Select")
				}) | border;
			});
	}
}
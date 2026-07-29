#pragma once

#include <vector>
#include <string>
#include <ftxui/component/component.hpp>

namespace ui {
	class MainMenu {
	public:
		MainMenu(std::function<void(int)> onSelect);

		ftxui::Component Create();

	private:
		std::function<void(int)> onSelect;

		std::vector<std::string> entries{
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
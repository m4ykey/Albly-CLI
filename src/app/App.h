#pragma once

#include <memory>
#include <functional>
#include <ftxui/component/component.hpp>

#include "../ui/MainMenu.h"
#include "../ui/SearchScreen.h"

namespace app {
	class App {
	public:
		App(std::function<void()> exitCallback);

		ftxui::Component Create();
	private:
		std::function<void()> exitCallback;

		std::unique_ptr<ui::MainMenu> mainMenu;
		std::unique_ptr<ui::SearchScreen> searchScreen;

		ftxui::Component container;
		int currentTab = 0;
	};
}
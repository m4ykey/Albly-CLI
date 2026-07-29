#pragma once

#include <memory>
#include <functional>
#include <ftxui/component/component.hpp>

#include "../ui/MainMenu.h"

namespace app {
	class App {
	public:
		App(std::function<void()> exitCallback);

		ftxui::Component Create();
	private:
		std::function<void()> exitCallback;
		std::unique_ptr<ui::MainMenu> mainMenu;
	};
}
#include "App.h"

namespace app {
	App::App(std::function<void()> exitCallback) : exitCallback(std::move(exitCallback)) {}

	ftxui::Component App::Create() {
		mainMenu = std::make_unique<ui::MainMenu>([this](int index) {
			if (index == 5) {
				exitCallback();
			}
			});

		return mainMenu->Create();
	}
}
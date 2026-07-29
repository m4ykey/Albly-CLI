#include "App.h"

namespace app {
	App::App(std::function<void()> exitCallback) : exitCallback(std::move(exitCallback)) {}

	ftxui::Component App::Create() {
		mainMenu = std::make_unique<ui::MainMenu>([this](int index) {
			if (index == 1) {
				currentTab = 1;
			}
			if (index == 5) {
				exitCallback();
			}
		});

		searchScreen = std::make_unique<ui::SearchScreen>([this]() {
			currentTab = 0;
		});

		container = ftxui::Container::Tab(
			{
				mainMenu->Create(),
				searchScreen->Create()
			},
			&currentTab
		);

		return container;
	}
}
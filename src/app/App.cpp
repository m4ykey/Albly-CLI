#include "App.h"

#include <cstdlib>
#include <stdexcept>
#include <string>
#include <fstream>

namespace app {
	App::App(std::function<void()> exitCallback) : exitCallback(std::move(exitCallback)) {}

	std::string loadApiKey() {
		std::ifstream file("config.properties");

		if (!file) {
			throw std::runtime_error("Cannot open config.properties");
		}

		std::string line;

		while (std::getline(file, line)) {
			const std::string prefix = "DISCOGS_API_KEY";

			if (line.starts_with(prefix)) {
				return line.substr(prefix.length());
			}
		}

		throw std::runtime_error("DISCOGS_API_KEY not found");
	}

	ftxui::Component App::Create() {
		const std::string apiKey = loadApiKey();

		searchAlbumService = std::make_unique<service::SearchAlbumService>(apiKey);

		mainMenu = std::make_unique<ui::MainMenu>([this](int index) {
			if (index == 0) {
				currentTab = 1;
			}
			if (index == 1) {
				currentTab = 2;
			}
			if (index == 5) {
				exitCallback();
			}
		});

		searchScreen = std::make_unique<ui::SearchScreen>(
			*searchAlbumService,
			[this]() {
				currentTab = 0;
			}
		);

		collectionScreen = std::make_unique<ui::CollectionScreen>([this]() {
			currentTab = 0;
		});

		container = ftxui::Container::Tab(
			{
				mainMenu->Create(),
				collectionScreen->Create(),
				searchScreen->Create()
			},
			&currentTab 
		);

		return container;
	}
}
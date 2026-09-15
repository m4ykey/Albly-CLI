#include "App.h"

#include <cstdlib>
#include <stdexcept>
#include <string>
#include <fstream>

#include <ftxui/component/event.hpp>

namespace app {
	App::App(
		ftxui::ScreenInteractive& screen,
		std::function<void()> exitCallback
	) : screen(screen),
		exitCallback(std::move(exitCallback)) {}

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
			screen,

			[this]() {
				currentTab = 0;
			},
			[this](int albumId) {
				selectedAlbumId = albumId;
				
				albumDetailScreen = std::make_unique<ui::AlbumDetailScreen>(
					[this]() {
						currentScreen = Screen::Main;
						currentTab = 2;
					},
					selectedAlbumId
				);

				currentScreen = Screen::AlbumDetail;
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

		auto root = ftxui::Renderer([this] {
			if (currentScreen == Screen::AlbumDetail && albumDetailScreen) {
				return albumDetailScreen->Create()->Render();
			}

			return container->Render();
		});

		root = root | ftxui::CatchEvent([this](ftxui::Event event) {
			if (currentScreen == Screen::Main) {
				return container->OnEvent(event);
			}

			return false;
		});

		return root;
	}
}
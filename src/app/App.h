#pragma once

#include <memory>
#include <functional>
#include <ftxui/component/component.hpp>

#include "../ui/MainMenu.h"
#include "../ui/SearchScreen.h"
#include "../ui/CollectionScreen.h"
#include "../ui/AlbumDetailScreen.h"
#include "../service/SearchAlbumService.h"

namespace app {
	class App {
	public:
		App(std::function<void()> exitCallback);

		ftxui::Component Create();
	private:
		enum class Screen {
			Main,
			AlbumDetail
		};

		std::function<void()> exitCallback;

		std::unique_ptr<ui::MainMenu> mainMenu;
		std::unique_ptr<ui::SearchScreen> searchScreen;
		std::unique_ptr<ui::CollectionScreen> collectionScreen;
		std::unique_ptr<ui::AlbumDetailScreen> albumDetailScreen;

		std::unique_ptr<service::SearchAlbumService> searchAlbumService;

		ftxui::Component container;

		int currentTab = 0;
		int selectedAlbumId = 0;

		Screen currentScreen = Screen::Main;
	};
}
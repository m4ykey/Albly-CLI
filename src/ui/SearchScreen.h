#pragma once

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>

#include <string>
#include <functional>
#include <vector>
#include <atomic>
#include <thread>
#include <mutex>
#include <optional>

#include "../service/SearchAlbumService.h"
#include "../model/SearchAlbumRoot.h"

namespace ui {
	class SearchScreen {
	public:
		SearchScreen(
			service::SearchAlbumService& searchAlbumService,
			ftxui::ScreenInteractive& screen,
			std::function<void()> onBack,
			std::function<void(int)> onAlbumClick
		);

		~SearchScreen();

		ftxui::Component Create();
	private:
		void StartSearch();
		void CheckSearchResult();

		service::SearchAlbumService& searchAlbumService;
		ftxui::ScreenInteractive& screen;

		ftxui::Component input;
		ftxui::Component resultsComponent;

		std::function<void()> onBack;
		std::function<void(int)> onAlbumClick;

		std::string query;

		std::vector<model::AlbumSearchResult> results;

		int selectedIndex = 0;

		int currentPage = 1;
		int totalPages = 1;

		bool searching = false;

		std::atomic<bool> loading = false;

		std::thread searchThread;

		std::mutex resultMutex;

		std::optional<model::SearchAlbumRoot> pendingResult;

		std::string errorMessage;
	};
}
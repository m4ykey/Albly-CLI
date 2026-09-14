#pragma once

#include <ftxui/component/component.hpp>
#include <string>
#include <functional>
#include <vector>

#include "../service/SearchAlbumService.h"
#include "../model/SearchAlbumRoot.h"

namespace ui {
	class SearchScreen {
	public:
		SearchScreen(
			service::SearchAlbumService& searchAlbumService,
			std::function<void()> onBack
		);

		ftxui::Component Create();
	private:
		std::string query;
		std::function<void()> onBack;

		std::vector<model::AlbumSearchResult> results;
		int selectedIndex = 0;

		int currentPage = 1;
		int totalPages = 1;

		bool searching = false;

		service::SearchAlbumService& searchAlbumService;
	};
}
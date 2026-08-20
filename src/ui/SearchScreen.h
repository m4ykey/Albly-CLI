#pragma once

#include <ftxui/component/component.hpp>
#include <string>
#include <functional>

#include "../service/SearchAlbumService.h"

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

		service::SearchAlbumService& searchAlbumService;
	};
}
#pragma once

#include <ftxui/component/component.hpp>
#include <functional>

namespace ui {
	class AlbumDetailScreen {
	public:
		AlbumDetailScreen(
			std::function<void()> onBack,
			int albumId
		);

		ftxui::Component Create();

	private:
		std::function<void()> onBack;
		int albumId;
	};
}
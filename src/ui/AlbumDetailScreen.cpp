#include "AlbumDetailScreen.h"

#include <ftxui/component/event.hpp>
#include <ftxui/dom/elements.hpp>

namespace ui {
	AlbumDetailScreen::AlbumDetailScreen(
		std::function<void()> onBack,
		int albumId
	) :
		onBack(std::move(onBack)),
		albumId(albumId) {  }

	ftxui::Component AlbumDetailScreen::Create() {
		using namespace ftxui;

		auto renderer = Renderer([this] {
			return vbox({
				text("ALBUM DETAIL") | bold | center,
				separator(),
				text("Album ID: " + std::to_string(albumId)),
				separator(),
				text("ESC BACK")
				}) | border;
			});

		return renderer | CatchEvent([this](Event event) {
			if (event == Event::Escape) {
				onBack();
				return true;
			}

			return false;
		});
	}
}
#include "SearchScreen.h"

#include <ftxui/dom/elements.hpp>
#include <ftxui/component/event.hpp>

namespace ui {
	SearchScreen::SearchScreen(
		service::SearchAlbumService& searchAlbumService,
		std::function<void()> onBack
	) : 
		searchAlbumService(searchAlbumService),
		onBack(std::move(onBack)) {  }

	ftxui::Component SearchScreen::Create() {
		using namespace ftxui;

		auto input = Input(&query, "Search...");

		auto layout = Container::Vertical({
			input
		});

		auto renderer = Renderer(layout, [this, input] {
			return vbox({
				text("SEARCH") | bold | center,
				separator(),
				hbox({ text("Search: "), input->Render() }),
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
#include "SearchScreen.h"

#include <ftxui/dom/elements.hpp>
#include <ftxui/component/event.hpp>

#include <iostream>

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
			Elements resultElements;

			for (int i = 0; i < static_cast<int>(results.size()); ++i) {
				const auto& album = results[i];

				auto element = hbox({
					text(i == selectedIndex ? "> " : " "),
					text(album.title)
				});

				if (i == selectedIndex) {
					element = element | inverted;
				}

				resultElements.push_back(element);
			}

			return vbox({
				text("SEARCH") | bold | center,
				separator(),
				hbox({ text("Search: "), input->Render() }),
				separator(),
				vbox(resultElements),
				separator(),
				text("↑ ↓ Select | Enter Search | Esc Back")
				}) | border;
			});

		return renderer | CatchEvent([this](Event event) {
			if (event == Event::ArrowDown) {
				if (!results.empty() && selectedIndex < static_cast<int>(results.size()) - 1) {
					++selectedIndex;
				}

				return true;
			}
			
			if (event == Event::ArrowUp) {
				if (selectedIndex > 0) {
					--selectedIndex;
				}

				return true;
			}

			if (event == Event::Return) {
				try {
					results = searchAlbumService.searchAlbum(query, 1);
					selectedIndex = 0;
				}
				catch (const std::exception& exception) {
					std::cerr << "Search failed: " << exception.what() << '\n';
				}

				return true;
			}

			if (event == Event::Escape) {
				onBack();
				return true;
			}
			return false;
		});
	}
}
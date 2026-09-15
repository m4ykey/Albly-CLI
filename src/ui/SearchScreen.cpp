#include "SearchScreen.h"

#include <ftxui/dom/elements.hpp>
#include <ftxui/component/event.hpp>

#include <iostream>

namespace ui {
	SearchScreen::SearchScreen(
		service::SearchAlbumService& searchAlbumService,
		std::function<void()> onBack,
		std::function<void(int)> onAlbumClick
	) : 
		searchAlbumService(searchAlbumService),
		onBack(std::move(onBack)),
		onAlbumClick(std::move(onAlbumClick)) {  }

	ftxui::Component SearchScreen::Create() {
		using namespace ftxui;

		auto input = Input(&query, "Search...");

		auto resultsComponent = Renderer([] {
			return text("Results");
		});

		auto layout = Container::Vertical({
			input,
			resultsComponent
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
				loading ? text("Loading...") | center : vbox(resultElements),
				separator(),
				text("Page " + std::to_string(currentPage) + " / " + std::to_string(totalPages)) | center,
				separator(),
				text("↑ ↓ Select | Enter Search | Esc Focus/Back | ←/J Previous Page | →/L Next Page | M Check Album")
				}) | border;
			});

		return renderer | CatchEvent([this, input, resultsComponent](Event event) {
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
				loading = true;

				try {
					auto searchResult = searchAlbumService.searchAlbum(query, currentPage);

					results = searchResult.results;
					totalPages = searchResult.pagination.pages;

					selectedIndex = 0;
					searching = false;
					resultsComponent->TakeFocus();
				}
				catch (const std::exception& exception) {
					std::cerr << "Search failed: " << exception.what() << '\n';
				}

				loading = false;

				return true;
			}

			if (event == Event::Escape) {
				if (!searching) {
					searching = true;
					input->TakeFocus();
					return true;
				}

				query.clear();
				results.clear();
				currentPage = 1;
				totalPages = 1;
				selectedIndex = 0;
				onBack();
				return true;
			}

			if (event == Event::ArrowRight || event == Event::L || event == Event::l) {
				if (currentPage < totalPages) {
					++currentPage;

					auto searchResult = searchAlbumService.searchAlbum(query, currentPage);

					results = searchResult.results;
					totalPages = searchResult.pagination.pages;
					selectedIndex = 0;
				}

				return true;
			}

			if (event == Event::ArrowLeft || event == Event::J || event == Event::j) {
				if (currentPage > 1) {
					--currentPage;

					auto searchResult = searchAlbumService.searchAlbum(query, currentPage);

					results = searchResult.results;
					totalPages = searchResult.pagination.pages;
					selectedIndex = 0;
				}

				return true;
			}

			if (event == Event::M || event == Event::m) {
				if (!results.empty()) {
					onAlbumClick(results[selectedIndex].master_id);
				}

				return true;
			}

			return false;
		});
	}
}
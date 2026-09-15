#include "SearchScreen.h"

#include <ftxui/dom/elements.hpp>
#include <ftxui/component/event.hpp>

#include <iostream>
#include <utility>

namespace ui {
	SearchScreen::SearchScreen(
		service::SearchAlbumService& searchAlbumService,
		ftxui::ScreenInteractive& screen,
		std::function<void()> onBack,
		std::function<void(int)> onAlbumClick
	) : 
		searchAlbumService(searchAlbumService),
		screen(screen),
		onBack(std::move(onBack)),
		onAlbumClick(std::move(onAlbumClick)) {  }

	SearchScreen::~SearchScreen() {
		if (searchThread.joinable()) {
			searchThread.join();
		}
	}

	void SearchScreen::StartSearch() {
		if (loading) {
			return;
		}

		if (query.empty()) {
			return;
		}

		loading = true;
		errorMessage.clear();

		const std::string searchQuery = query;
		const int searchPage = currentPage;

		if (searchThread.joinable()) {
			searchThread.join();
		}

		searchThread = std::thread([this, searchQuery, searchPage]() {
			try {
				auto searchResult = searchAlbumService.searchAlbum(searchQuery, searchPage);
				{
					std::lock_guard<std::mutex> lock(resultMutex);
					pendingResult = std::move(searchResult);
				}
			}
			catch (const std::exception& exception) {
				std::lock_guard<std::mutex> lock(resultMutex);
				errorMessage = exception.what();
			}

			loading = false;

			screen.PostEvent(ftxui::Event::Custom);
		});
	}

	void SearchScreen::CheckSearchResult() {
		if (loading) {
			return;
		}

		std::lock_guard<std::mutex> lock(resultMutex);

		if (pendingResult) {
			results = pendingResult->results;
			totalPages = pendingResult->pagination.pages;
			selectedIndex = 0;
			searching = false;

			pendingResult.reset();

			if (resultsComponent) {
				resultsComponent->TakeFocus();
			}
		}
	}

	ftxui::Component SearchScreen::Create() {
		using namespace ftxui;

		input = Input(&query, "Search...");

		resultsComponent = Renderer([] {
			return text("Results");
		});

		auto layout = Container::Vertical({
			input,
			resultsComponent
		});

		auto renderer = Renderer(layout, [this] {
			CheckSearchResult();

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

			Element content;

			if (loading) {
				content = text("Loading...") | center;
			}
			else if (!errorMessage.empty()) {
				content = text("Search failed: " + errorMessage) | center;
			}
			else if (results.empty()) {
				content = text("No results") | center;
			}
			else {
				content = vbox(resultElements);
			}

			return vbox({
				text("SEARCH") | bold | center,
				separator(),
				hbox({ text("Search: "), input->Render() }),
				separator(),
				content,
				separator(),
				text("Page " + std::to_string(currentPage) + " / " + std::to_string(totalPages)) | center,
				separator(),
				text("↑ ↓ Select | Enter Search | Esc Focus/Back | ←/J Previous Page | →/L Next Page | M Check Album")
				}) | border;
			});

		return renderer | CatchEvent([this](Event event) {
			if (loading) {
				return true;
			}

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
				StartSearch();

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

				searching = false;

				onBack();

				return true;
			}

			if (event == Event::ArrowRight || event == Event::L || event == Event::l) {
				if (currentPage < totalPages) {
					++currentPage;

					StartSearch();
				}

				return true;
			}

			if (event == Event::ArrowLeft || event == Event::J || event == Event::j) {
				if (currentPage > 1) {
					--currentPage;

					StartSearch();
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
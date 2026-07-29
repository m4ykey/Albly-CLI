#include "CollectionScreen.h"

#include <ftxui/component/event.hpp>
#include <ftxui/dom/elements.hpp>

namespace ui {
	CollectionScreen::CollectionScreen(std::function<void()> onBack)
		: onBack(std::move(onBack)) {  }

	ftxui::Component CollectionScreen::Create() {
		using namespace ftxui;

		auto renderer = Renderer([this]{
			return vbox({
				text("COLLECTION") | bold | center,
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
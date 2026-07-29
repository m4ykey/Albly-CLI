#pragma once

#include <ftxui/component/component.hpp>
#include <string>
#include <functional>

namespace ui {
	class SearchScreen {
	public:
		SearchScreen(std::function<void()> onBack);

		ftxui::Component Create();
	private:
		std::string query;
		std::function<void()> onBack;
	};
}
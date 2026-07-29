#pragma once

#include <functional>
#include <string>
#include <ftxui/component/component.hpp>

namespace ui {
	class CollectionScreen {
	public:
		CollectionScreen(std::function<void()> onBack);

		ftxui::Component Create();
	private:
		std::function<void()> onBack;
	};
}
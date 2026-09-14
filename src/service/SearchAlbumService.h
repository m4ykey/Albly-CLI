#pragma once

#include <vector>
#include <string>
#include "../model/SearchAlbumRoot.h"

namespace service {

	class SearchAlbumService {
	public:
		SearchAlbumService(const std::string& apiKey);

		model::SearchAlbumRoot searchAlbum(
			const std::string& query, 
			int page
		);

	private:
		std::string buildSearchUrl(
			const std::string& query,
			int page
		);

		std::string apiKey;
		static constexpr int PAGE_SIZE = 20;
	};
}
#pragma once

#include <vector>
#include <string>

namespace model {

	struct AlbumSearchResult {
		std::string title;
		std::string thumb;
		std::string cover_image;
		int id = 0;
		int master_id = 0;
	};

	struct SearchAlbumRoot {
		std::vector<AlbumSearchResult> results;
	};
}
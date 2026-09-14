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

	struct Pagination {
		int page = 0;
		int pages = 0;
		int per_page = 0;
		int items = 0;
	};

	struct SearchAlbumRoot {
		Pagination pagination;
		std::vector<AlbumSearchResult> results;
	};
}
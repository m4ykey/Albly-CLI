#pragma once

#include <vector>
#include <string>

namespace dto {

	struct AlbumSearchResultDto {
		std::string title;
		std::string thumb;
		std::string cover_image;
		int id = 0;
		int master_id = 0;
	};

	struct PaginationDto {
		int page = 0;
		int pages = 0;
		int per_page = 0;
		int items = 0;
	};

	struct SearchAlbumRootDto {
		PaginationDto pagination;
		std::vector<AlbumSearchResultDto> results;
	};
}
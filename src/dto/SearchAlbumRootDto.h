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

	struct SearchAlbumRootDto {
		std::vector<AlbumSearchResultDto> results;
	};
}
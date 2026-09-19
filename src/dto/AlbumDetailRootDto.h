#pragma once

#include <string>
#include <vector>

namespace dto {

	struct AlbumDetailRootDto {
		int id = 0;
		int main_release = 0;
		int most_recent_release = 0;
		std::string resource_url;
		std::string versions_url;
		std::string main_release_url;
		std::string most_recent_release_url;
		int year = 0;
		std::string title;
		std::string uri;
		std::vector<ArtistDto> artists;
		std::vector<TrackListDto> tracklist;
	};

	struct ArtistsDto {
		std::string name;
	};

	struct TrackListDto {
		std::string position;
		std::string type_;
		std::string title;
		std::string duration;
	};
}
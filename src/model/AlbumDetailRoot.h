#pragma once

#include <string>
#include <vector>

namespace model {

	struct AlbumDetailRoot {
		int id = 0;
		int year = 0;
		std::string title;
		std::vector<Artists> artists;
		std::vector<TrackList> tracklist;
		std::string uri;
	};

	struct Artists {
		std::string name;
	};

	struct TrackList {
		std::string position;
		std::string type;
		std::string title;
		std::string duration;
	};

}
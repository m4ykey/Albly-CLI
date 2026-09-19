#pragma once

#include <vector>
#include <string>
#include "../model/AlbumDetailRoot.h"

namespace service {

	class AlbumDetailService {
	public:
		AlbumDetailService(const std::string& apiKey);

		model::AlbumDetailRoot getAlbum(int albumId);

	private:
		std::string buildDetailUrl(int albumId);

		std::string apiKey;
	};
}
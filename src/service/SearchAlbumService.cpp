#include "SearchAlbumService.h"

#include <stdexcept>
#include <httplib.h>
#include <nlohmann/json.hpp>

namespace service {
	
	SearchAlbumService::SearchAlbumService(const std::string& apiKey) : apiKey(apiKey) {}

	std::string SearchAlbumService::buildSearchUrl(
		const std::string& query,
		int page
	) {
		std::string url = "/database/search";

		url += "?q=" + query +
			"&format=album" +
			"&type=master" +
			"&per_page=" + std::to_string(PAGE_SIZE) +
			"&page=" + std::to_string(page) +
			"&token=" + apiKey;
		
		return url;
	}
	
	std::vector<model::AlbumSearchResult> SearchAlbumService::searchAlbum(
		const std::string& query,
		int page
	) {
		if (query.empty()) {
			throw std::invalid_argument("Query cannot be empty");
		}

		if (page < 1) {
			throw std::invalid_argument("Page must be at least 1");
		}

		std::string url = buildSearchUrl(query, page);

		httplib::Client client("https://api.discogs.com");

		auto response = client.Get(url);

		if (!response) {
			throw std::runtime_error("Failed to connect to Discogs");
		}

		if (response->status != 200) {
			throw std::runtime_error("Discogs API returned an error");
		}

		std::string body = response->body;

		nlohmann::json data = nlohmann::json::parse(body);

		for (const auto& item : data["results"]) {
			
		}
	}
}
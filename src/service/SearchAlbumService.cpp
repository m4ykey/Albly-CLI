#include "SearchAlbumService.h"

#include <stdexcept>
#include <httplib.h>
#include <nlohmann/json.hpp>

#include "../dto/SearchAlbumRootDto.h"
#include "../mapper/SearchAlbumMapper.h"

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
			"&token" + apiKey;
		
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
			throw std::runtime_error(
				"Discogs API returned status: " +
				std::to_string(response->status) +
				"\nResponse: " + 
				response->body
			);
		}

		std::string body = response->body;

		nlohmann::json data = nlohmann::json::parse(body);

		dto::SearchAlbumRootDto result;

		for (const auto& item : data["results"]) {
			dto::AlbumSearchResultDto album;

			album.title = item["title"];
			album.cover_image = item["cover_image"];
			album.id = item["id"];
			album.thumb = item["thumb"];

			if (item.contains("master_id") && !item["master_id"].is_null()) {
				album.master_id = item["master_id"];
			}

			result.results.push_back(album);
		}

		model::SearchAlbumRoot domainResults = mapper::mapToDomain(result);

		return domainResults.results;
	}
}
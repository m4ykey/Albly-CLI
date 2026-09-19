#include "AlbumDetailService.h"

#include <httplib.h>
#include <stdexcept>
#include <nlohmann/json.hpp>

#include "../dto/AlbumDetailRootDto.h"
#include "../mapper/AlbumDetailMapper.h"

namespace service {

	AlbumDetailService::AlbumDetailService(const std::string& apiKey) : apiKey(apiKey) {}

	std::string AlbumDetailService::buildDetailUrl(int albumId) {
		std::string url = "/masters";

		url += "/" + std::to_string(albumId) + "?token=" + apiKey;

		return url;
	}

	model::AlbumDetailRoot AlbumDetailService::getAlbum(int albumId) {
		std::string url = buildDetailUrl(albumId);

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

		dto::AlbumDetailRootDto result;

		result.id = data["id"];
		result.year = data["year"];
		result.title = data["title"];
		result.uri = data["uri"];

		for (const auto& item : data["artists"]) {
			dto::ArtistsDto artist;

			artist.name = item["name"];

			result.artists.push_back(artist);
		}

		for (const auto& item : data["tracklist"]) {
			dto::TrackListDto trackList;

			trackList.title = item["title"];
			trackList.type_ = item["type"];
			trackList.duration = item["duration"];
			trackList.position = item["position"];

			result.tracklist.push_back(trackList);
		}

		model::AlbumDetailRoot domainResult = mapper::mapToDomain(result);
		return domainResult;
	}

}
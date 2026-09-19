#include "AlbumDetailMapper.h"

namespace mapper {

	model::Artists mapToArtistDomain(const dto::ArtistsDto& dto) {
		return model::Artists{
			dto.name
		};
	}

	model::TrackList mapToTrackListDomain(const dto::TrackListDto& dto) {
		return model::TrackList{
			dto.position,
			dto.type_,
			dto.title,
			dto.duration
		};
	}

	model::AlbumDetailRoot mapToDomain(const dto::AlbumDetailRootDto& dto) {
		std::vector<model::Artists> artists;
		std::vector<model::TrackList> tracklist;

		artists.reserve(dto.artists.size());
		tracklist.reserve(dto.tracklist.size());

		for (const auto& artist : dto.artists) {
			artists.push_back(mapToArtistDomain(artist));
		}

		for (const auto& track : dto.tracklist) {
			tracklist.push_back(mapToTrackListDomain(track));
		}
		
		return model::AlbumDetailRoot{
			dto.id,
			dto.year,
			dto.title,
			artists,
			tracklist,
			dto.uri,
		};
	}
}
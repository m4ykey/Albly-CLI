#pragma once

#include "../dto/AlbumDetailRootDto.h"
#include "../model/AlbumDetailRoot.h"

namespace mapper {

	model::AlbumDetailRoot mapToDomain(const dto::AlbumDetailRootDto& dto);
	model::Artists mapToArtistDomain(const dto::ArtistsDto& dto);
	model::TrackList mapToTrackListDomain(const dto::TrackListDto& dto);

}
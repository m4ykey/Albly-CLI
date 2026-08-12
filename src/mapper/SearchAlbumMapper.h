#pragma once

#include "../dto/SearchAlbumRootDto.h"
#include "../model/SearchAlbumRoot.h"

namespace mapper {

	model::AlbumSearchResult mapToDomain(const dto::AlbumSearchResultDto& dto);
	model::SearchAlbumRoot mapToDomain(const dto::SearchAlbumRootDto& dto);

}
#include "SearchAlbumMapper.h"

namespace mapper {

	model::AlbumSearchResult mapToDomain(const dto::AlbumSearchResultDto& dto) {
		return model::AlbumSearchResult{
			dto.title,
			dto.thumb,
			dto.cover_image,
			dto.id,
			dto.master_id
		};
	}

	model::SearchAlbumRoot mapToDomain(const dto::SearchAlbumRootDto& dto) {
		std::vector<model::AlbumSearchResult> results;
		results.reserve(dto.results.size());
		
		for (const auto& result : dto.results) {
			results.push_back(mapToDomain(result));
		}

		return model::SearchAlbumRoot{
			results
		};
	}
}
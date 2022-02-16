#include "File.h"

git::File::File(const std::string& filePath, git_status_t fileStatus)
    : path(filePath), status(fileStatus) {}

bool git::File::IsStaged() const {
	return status == GIT_STATUS_INDEX_MODIFIED || status == GIT_STATUS_INDEX_NEW ||
	       status == GIT_STATUS_INDEX_DELETED || status == GIT_STATUS_INDEX_RENAMED ||
	       status == GIT_STATUS_INDEX_TYPECHANGE;
}

git::FileState git::File::GetFileState() const {
	switch (status) {
		case GIT_STATUS_INDEX_NEW:
		case GIT_STATUS_WT_NEW:
			return git::FileState::New;
			break;
		case GIT_STATUS_INDEX_MODIFIED:
		case GIT_STATUS_WT_MODIFIED:
			return git::FileState::Modified;
			break;
		case GIT_STATUS_INDEX_DELETED:
		case GIT_STATUS_WT_DELETED:
			return git::FileState::Deleted;
			break;
		case GIT_STATUS_INDEX_RENAMED:
		case GIT_STATUS_WT_RENAMED:
			return git::FileState::Renamed;
			break;
		case GIT_STATUS_INDEX_TYPECHANGE:
		case GIT_STATUS_WT_TYPECHANGE:
			return git::FileState::Typechange;
			break;
		default:
			return git::FileState::None;
	}
}

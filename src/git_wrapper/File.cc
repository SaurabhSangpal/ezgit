#include "File.h"

git::File::File(const std::string& filePath, git_status_t fileStatus)
    : path(filePath), status(fileStatus) {}

bool git::File::IsStaged() const {
	return status == GIT_STATUS_INDEX_MODIFIED || status == GIT_STATUS_INDEX_NEW ||
	       status == GIT_STATUS_INDEX_DELETED || status == GIT_STATUS_INDEX_RENAMED ||
	       status == GIT_STATUS_INDEX_TYPECHANGE;
}

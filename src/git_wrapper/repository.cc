#include "Repository.h"

#include <git2.h>

bool git::Repository::Create(const char* path) noexcept {
	repoLocation = path;
	int error    = git_repository_init(&repo, path, 0);
	return error == 0;
}

bool git::Repository::Open(const char* path) noexcept {
	repoLocation = path;
	int error    = git_repository_open(&repo, path);
	return error == 0;
}

bool git::Repository::Clone(const char* url, const char* directory) noexcept {
	repoLocation = directory;
	int error    = git_clone(&repo, url, directory, NULL);
	return error == 0;
}

std::vector<std::string> git::Repository::GetModifiedFiles() noexcept {
	std::vector<std::string> modifiedFiles;

	git_status_list* status;
	if (git_repository_is_bare(repo))  // should probably log here.
		return modifiedFiles;

	if (git_status_list_new(&status, repo, NULL) != 0) return modifiedFiles;

	auto numEntries = git_status_list_entrycount(status);

	const git_status_entry* statusEntry;
	const char *		oldPath, *newPath;
	for (int i = 0; i < numEntries; i++) {
		oldPath = newPath = nullptr;
		statusEntry	  = git_status_byindex(status, i);

		if (statusEntry->status == GIT_STATUS_CURRENT) continue;

		// TODO: Differentiate between staged and unstaged files.
		switch (statusEntry->status) {
			case GIT_STATUS_INDEX_NEW:
			case GIT_STATUS_INDEX_MODIFIED:
			case GIT_STATUS_INDEX_DELETED:
			case GIT_STATUS_INDEX_RENAMED:
			case GIT_STATUS_INDEX_TYPECHANGE:
			case GIT_STATUS_WT_NEW:
			case GIT_STATUS_WT_MODIFIED:
			case GIT_STATUS_WT_DELETED:
			case GIT_STATUS_WT_RENAMED:
			case GIT_STATUS_WT_TYPECHANGE:
				break;
			default:
				continue;
		}

		if (statusEntry->head_to_index) {
			oldPath = statusEntry->head_to_index->old_file.path;
			newPath = statusEntry->head_to_index->new_file.path;
		} else if (statusEntry->index_to_workdir) {
			oldPath = statusEntry->index_to_workdir->old_file.path;
			newPath = statusEntry->index_to_workdir->new_file.path;
		}

		std::string string;
		if (oldPath && newPath && strcmp(oldPath, newPath)) {
			string = std::string(("%s  %s", oldPath, newPath));
		} else {
			string = std::string(oldPath ? oldPath : newPath);
		}
		modifiedFiles.push_back(string);
	}

	return modifiedFiles;
}

#include "Repository.h"
#include "File.h"

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

std::vector<git::File> git::Repository::GetChangedFiles() noexcept {
	std::vector<git::File> modifiedFiles;

	git_status_list* status;
	if (IsBare())  // should probably log here.
		return modifiedFiles;

	if (git_status_list_new(&status, repo, NULL) != 0) return modifiedFiles;

	auto numEntries = git_status_list_entrycount(status);

	const git_status_entry* statusEntry;
	const char *		oldPath, *newPath;
	for (int i = 0; i < numEntries; i++) {
		oldPath = newPath = nullptr;
		statusEntry	  = git_status_byindex(status, i);

		if (statusEntry->status == GIT_STATUS_CURRENT) continue;

		if (!ShouldProcess(statusEntry->status)) continue;

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
		auto file = File(oldPath, newPath, statusEntry->status);
		modifiedFiles.push_back(file);
	}

	return modifiedFiles;
}

bool git::Repository::IsBare() const noexcept { return git_repository_is_bare(repo); }

bool git::Repository::ShouldProcess(git_status_t status) {
	return status == GIT_STATUS_INDEX_NEW || status == GIT_STATUS_INDEX_MODIFIED ||
	       status == GIT_STATUS_INDEX_DELETED || status == GIT_STATUS_INDEX_RENAMED ||
	       status == GIT_STATUS_INDEX_TYPECHANGE || status == GIT_STATUS_WT_NEW ||
	       status == GIT_STATUS_WT_MODIFIED || status == GIT_STATUS_WT_DELETED ||
	       status == GIT_STATUS_WT_RENAMED || status == GIT_STATUS_WT_TYPECHANGE;
}
#include "Repository.h"

#include <git2.h>

bool git::Repository::Create(const char* path) noexcept {
	int error = git_repository_init(&repo, path, 0);
	return error == 0;
}

bool git::Repository::Open(const char* path) noexcept {
	int error = git_repository_open(&repo, path);
	return error == 0;
}

bool git::Repository::Clone(const char* url, const char* directory) noexcept {
	int error = git_clone(&repo, url, directory, NULL);
	return error == 0;
}

git_status_list** git::Repository::Status() noexcept {
	git_status_list** list{};
	int		  error = git_status_list_new(list, repo, NULL);
	if (error == 0) {
		return list;
	}

	return nullptr;
}

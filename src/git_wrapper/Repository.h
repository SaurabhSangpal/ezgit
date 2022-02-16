#pragma once

#include <git2/status.h>
#include <qapplication.h>

#include <string>
#include <vector>

#include "Remote.h"

struct git_repository;
struct git_status_list;

namespace git {
class Repository {
    public:
	Repository()  = default;
	~Repository() = default;

	// Returns true if repository is created successfully.
	bool Create(const char* path) noexcept;
	// Returns true if repository is opened successfully.
	bool Open(const char* path) noexcept;
	// Returns true if repository is cloned successfully.
	bool Clone(const char* url, const char* directory) noexcept;

	// Gets list of new/modified/renamed/deleted/typechanged files in the status list.
	// TODO: Differentiate between staged and unstaged files.
	// TODO: Differentiate between new/modified/deleted/moved, etc files.
	[[nodiscard]] std::vector<std::string> GetChangedFiles() noexcept;

	// Returns true if the repository is bare.
	[[nodiscard]] bool IsBare() const noexcept;

	// Returns true if repo is not null.
	[[nodiscard]] bool IsValid() const noexcept { return repo != nullptr; }

	[[nodiscard]] git_repository* GetRepository() const noexcept { return repo; }

	[[nodiscard]] std::string GetRepoLocation() const noexcept { return repoLocation; }

    private:
	git_repository*		 repo;
	std::string		 repoLocation;
	std::vector<git::Remote> remotes;
};
}  // namespace git
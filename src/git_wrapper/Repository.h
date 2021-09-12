#pragma once

#include <QApplication.h>

struct git_repository;

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

	bool IsGitRepoNonNull() const noexcept { return repo != nullptr; }

    private:
	git_repository* repo;
};
}  // namespace git
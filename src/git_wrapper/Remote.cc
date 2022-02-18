#include "Remote.h"

#include <git2.h>

#include "Repository.h"

git::Remote::Remote(git_remote* remote) noexcept : remote(remote) {}

git::Remote::~Remote() noexcept {
	// TODO: Fix exception thrown here at exit.
	//git_remote_free(remote);
}

bool git::Remote::Create(const std::string& name, const std::string& url,
			 const git::Repository& repo) noexcept {
	int error = git_remote_create(&remote, repo.GetRepository(), name.c_str(), url.c_str());
	return error == 0;
}

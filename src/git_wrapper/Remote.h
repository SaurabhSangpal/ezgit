#pragma once

#include <string>

struct git_remote;

namespace git {
class Repository;
class Remote {
    public:
	Remote() = default;
	bool Create(const std::string& name, const std::string& url,
		    const git::Repository& repo) noexcept;

    private:
	git_remote* remote;
};
}  // namespace git
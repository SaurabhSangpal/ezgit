#pragma once

#include <git2.h>
#include <QApplication.h>

namespace git {
class repository {
    public:
	repository()  = default;
	~repository() = default;

	void create(const char* path) noexcept;
	void open(const char* path) noexcept;

    private:
	git_repository* repo;
};
}  // namespace git
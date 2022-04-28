#pragma once
#include <git2/status.h>

#include <string>

namespace git {
enum class FileState { None, New, Modified, Deleted, Renamed, Typechange };

class File {
    public:
	File(const std::string& oldPath, const std::string& newPath, git_status_t fileStatus);

	const std::string& GetPath() const { return oldPath.empty() ? newPath : oldPath; }

	// Is the file staged for committing?
	bool IsStaged() const;

	FileState GetFileState() const;

    private:
	std::string  oldPath, newPath;
	git_status_t status;
};
}  // namespace git
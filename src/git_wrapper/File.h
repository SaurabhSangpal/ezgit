#pragma once
#include <git2/status.h>

#include <string>

namespace git {
enum class FileState { None, New, Modified, Deleted, Renamed, Typechange };

class File {
    public:
	File(const std::string& filePath, git_status_t fileStatus);

	const std::string& GetPath() { return path; }

	bool IsStaged() const;

	FileState GetFileState() const;

    private:
	std::string  path;
	git_status_t status;
};
}  // namespace git
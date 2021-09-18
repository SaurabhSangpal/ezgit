#pragma once

#include <string>

namespace git {
class Commit {
    public:
	Commit()  = default;
	~Commit() = default;

	// Helper method, remove if not required.
	void Setup(const std::string& m, const std::string& a, const std::string& h,
		   const std::string& d) noexcept;

	const std::string& GetMessage() const noexcept { return message; }
	const std::string& GetAuthor() const noexcept { return author; }
	const std::string& GetHash() const noexcept { return hash; }
	const std::string& GetDate() const noexcept { return date; }

    private:
	std::string message;
	std::string author;
	std::string hash;
	std::string date;
};
}  // namespace git
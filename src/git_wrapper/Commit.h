#pragma once

#include <string>

namespace git {
class Commit {
    public:
	Commit()  = default;
	~Commit() = default;

	// Helper method, remove if not required.
	void Setup(const std::string& m, const std::string& a, const std::string& h,
		   const std::string& d, const std::string& b) noexcept;

	[[nodiscard]] const std::string& GetMessage() const noexcept { return message; }
	[[nodiscard]] const std::string& GetAuthor() const noexcept { return author; }
	[[nodiscard]] const std::string& GetHash() const noexcept { return hash; }
	[[nodiscard]] const std::string& GetDate() const noexcept { return date; }
	[[nodiscard]] const std::string& GetBody() const noexcept { return body; }

    private:
	std::string message;
	std::string author;
	std::string hash;
	std::string date;
	std::string body;
};
}  // namespace git
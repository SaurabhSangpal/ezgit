#include "Commit.h"

void git::Commit::Setup(const std::string& m, const std::string& a, const std::string& h,
			const std::string& d, const std::string& b) noexcept {
	message = m;
	author	= a;
	hash	= h;
	date	= d;
	body	= b;
}
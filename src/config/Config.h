#pragma once
#include <QString>

class QFile;

class Config {
    public:
	Config() = default;
	~Config() noexcept;

	void CreateOrLoadConfigFile() noexcept;
	void CreateOrLoadHistoryFile() noexcept;

    private:
	QFile* configFile  = nullptr;
	QFile* historyFile = nullptr;
};

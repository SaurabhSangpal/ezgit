#pragma once
#include <QString>

class QFile;

class Config {
    public:
	const QString ConfigFileRelativePath = "config.json";
	const QString HistoryRelativePath    = "history.json";

	~Config();

	void CreateOrLoadConfigFile() noexcept;
	void CreateOrLoadHistoryFile() noexcept;

    private:
	QFile* configFile  = nullptr;
	QFile* historyFile = nullptr;
};

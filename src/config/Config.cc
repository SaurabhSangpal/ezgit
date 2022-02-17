#include "Config.h"

#include <QFile>
#include <QStandardPaths>

const QString ConfigFileName  = "config.json";
const QString HistoryFileName = "history.json";

Config::~Config() noexcept {
	delete configFile;
	delete historyFile;
}

void Config::CreateOrLoadConfigFile() noexcept {
	auto path = QStandardPaths::locate(QStandardPaths::AppConfigLocation, ConfigFileName);

	configFile = new QFile(path);
}

void Config::CreateOrLoadHistoryFile() noexcept {
	auto path = QStandardPaths::locate(QStandardPaths::AppConfigLocation, HistoryFileName);

	historyFile = new QFile(path);
}

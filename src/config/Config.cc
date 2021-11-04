#include "Config.h"

#include <QFile>
#include <QStandardPaths>

Config::~Config() {
	delete configFile;
	delete historyFile;
}

void Config::CreateOrLoadConfigFile() noexcept {
	auto path = QStandardPaths::locate(QStandardPaths::ConfigLocation, ConfigFileRelativePath);

	configFile = new QFile("ConfigFile");
}

void Config::CreateOrLoadHistoryFile() noexcept {}

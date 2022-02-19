#include "ChangedFile.h"

#include <QCheckBox>
#include <QHBoxLayout>
#include <QLabel>
#include <string>

#include "../git_wrapper/File.h"

const std::string GetPrefixByFileState(git::FileState state);

ChangedFile::ChangedFile(QWidget* parent) noexcept {
	setParent(parent);

	auto* layout = new QHBoxLayout(this);
	layout->setMargin(0);
	layout->setSpacing(1);
	this->setLayout(layout);

	prefix = new QLabel(this);
	layout->addWidget(prefix);

	path = new QLabel(this);
	layout->addWidget(path);

	checkBox = new QCheckBox(this);
	layout->addWidget(checkBox);

	show();
}

void ChangedFile::Setup(const git::File& file) noexcept {
	prefix->setText(QString::fromStdString(GetPrefixByFileState(file.GetFileState())));
	path->setText(QString::fromStdString(file.GetPath()));
	checkBox->setCheckState(file.IsStaged() ? Qt::CheckState::Checked
						: Qt::CheckState::Unchecked);
	checkBox->setText(QString());  // We don't need text in checkBox.
}

constexpr std::string_view New	      = "New:";
constexpr std::string_view Modified   = "Mod:";
constexpr std::string_view Deleted    = "Del:";
constexpr std::string_view Renamed    = "Ren:";
constexpr std::string_view Typechange = "Typ:";

const std::string GetPrefixByFileState(git::FileState state) {
	switch (state) {
		case git::FileState::New:
			return New.data();
			break;
		case git::FileState::Modified:
			return Modified.data();
			break;
		case git::FileState::Deleted:
			return Deleted.data();
			break;
		case git::FileState::Renamed:
			return Renamed.data();
			break;
		case git::FileState::Typechange:
			return Typechange.data();
			break;
		default:
			return "Non";
			break;
	}
}

#include "YourChanges.h"

#include <git2.h>
#include <qframe.h>
#include <qlabel.h>
#include <qlayout.h>

#include "../git_wrapper/File.h"
#include "../git_wrapper/Repository.h"
#include "ChangedFile.h"

YourChanges::YourChanges(git::Repository& repo, QWidget* parent) {
	setParent(parent);

	auto* gitRepository = repo.GetRepository();
	index		    = nullptr;
	if (git_repository_index(&index, gitRepository) != 0) return;

	auto* layout = new QVBoxLayout(this);
	layout->setMargin(0);
	layout->setSpacing(1);
	setLayout(layout);

	staged = new QFrame(this);
	layout->addWidget(staged);
	auto* stagedLayout = new QVBoxLayout(staged);
	staged->setLayout(stagedLayout);

	unstaged = new QFrame(this);
	layout->addWidget(unstaged);
	auto* unstagedLayout = new QVBoxLayout(unstaged);
	unstaged->setLayout(unstagedLayout);

	// Fetch status
	auto files = repo.GetChangedFiles();
	for (auto& file : files) {
		auto* changedFile = new ChangedFile(this);
		changedFile->Setup(file);
		// auto* label  = new QLabel(this);
		// auto  string = QString::fromStdString(file.GetPath());
		// label->setText(string);
		if (file.IsStaged())
			stagedLayout->addWidget(changedFile);
		else
			unstagedLayout->addWidget(changedFile);
	}
}

YourChanges::~YourChanges() noexcept { git_index_free(index); }

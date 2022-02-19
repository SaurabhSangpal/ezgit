#include "YourChanges.h"

#include <git2.h>

#include <QFrame>
#include <QLabel>
#include <QLayout>
#include <QPushButton>

#include "../git_wrapper/File.h"
#include "../git_wrapper/Repository.h"
#include "ChangedFile.h"

YourChanges::YourChanges(git::Repository& repo, QWidget* parent) {
	setParent(parent);

	constexpr int ButtonWidth  = 80;
	constexpr int ButtonHeight = 30;

	// Top level
	auto* layout = new QVBoxLayout(this);
	layout->setMargin(0);
	layout->setSpacing(1);
	setLayout(layout);

	// Staged
	auto* stagedTitleFrame = new QFrame(this);
	stagedTitleFrame->setFixedHeight(ButtonHeight * 2);
	layout->addWidget(stagedTitleFrame);
	auto* stagedTitleLayout = new QHBoxLayout(stagedTitleFrame);
	stagedTitleFrame->setLayout(stagedTitleLayout);

	stagedLabel = new QLabel(this);
	stagedLabel->setText("Staged");
	stagedTitleLayout->addWidget(stagedLabel);

	unstageButton = new QPushButton(this);
	unstageButton->setFixedSize(QSize(ButtonWidth, ButtonHeight));
	unstageButton->setText("Unstage");
	stagedTitleLayout->addWidget(unstageButton);

	staged = new QFrame(this);
	layout->addWidget(staged);
	auto* stagedLayout = new QVBoxLayout(staged);
	stagedLayout->setAlignment(Qt::AlignTop);
	staged->setLayout(stagedLayout);

	// Unstaged
	auto* unstagedTitleFrame = new QFrame(this);
	unstagedTitleFrame->setFixedHeight(ButtonHeight * 2);
	layout->addWidget(unstagedTitleFrame);
	auto* unstagedTitleLayout = new QHBoxLayout(unstagedTitleFrame);
	unstagedTitleFrame->setLayout(unstagedTitleLayout);

	unstagedLabel = new QLabel(this);
	unstagedLabel->setText("Unstaged");
	unstagedTitleLayout->addWidget(unstagedLabel);

	stageButton = new QPushButton(this);
	stageButton->setFixedSize(QSize(ButtonWidth, ButtonHeight));
	stageButton->setText("Stage");
	unstagedTitleLayout->addWidget(stageButton);

	unstaged = new QFrame(this);
	layout->addWidget(unstaged);
	auto* unstagedLayout = new QVBoxLayout(unstaged);
	unstagedLayout->setAlignment(Qt::AlignTop);
	unstaged->setLayout(unstagedLayout);

	// Fetch status
	auto files = repo.GetChangedFiles();
	for (auto& file : files) {
		auto* changedFile = new ChangedFile(this);
		changedFile->Setup(file);
		if (file.IsStaged())
			stagedLayout->addWidget(changedFile);
		else
			unstagedLayout->addWidget(changedFile);
	}
}

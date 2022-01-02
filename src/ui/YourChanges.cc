#include "YourChanges.h"

#include <git2.h>
#include <qframe.h>
#include <qlayout.h>

#include "../git_wrapper/Repository.h"

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
}

YourChanges::~YourChanges() noexcept { git_index_free(index); }

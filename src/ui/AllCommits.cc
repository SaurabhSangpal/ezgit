#include "AllCommits.h"

#include <memory>

#include "../git_wrapper/Commit.h"
#include "Commit.h"
#include "ui_AllCommits.h"

AllCommits::AllCommits(QWidget* parent) : QWidget(parent), ui(new Ui::AllCommits) {
	ui->setupUi(this);

	git::Commit commit;
	commit.Setup("Add generic comment", "Saurabh Sangpal", "asch23kcks", "18 Sep 2021 18:30");

	auto* layout = new QVBoxLayout;
	layout->setAlignment(Qt::AlignmentFlag::AlignTop);
	ui->commitsScrollAreaContent->setLayout(layout);

	for (int i = 0; i < 10; i++) {
		AddCommit(commit);
	}
	ui->commitsScrollArea->setWidget(ui->commitsScrollAreaContent);
}

AllCommits::~AllCommits() { delete ui; }

void AllCommits::AddCommit(const git::Commit& commit) noexcept {
	auto uiCommit = std::make_shared<Commit>(ui->commitsScrollAreaContent);
	uiCommit->Setup(commit);
	ui->commitsScrollAreaContent->layout()->addWidget(uiCommit.get());

	commits.push_back(uiCommit);
}

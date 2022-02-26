#include "Commit.h"

#include <QFont>
#include <QLabel>
#include <QLayout>
#include <QPushButton>

#include "../git_wrapper/Commit.h"

QFont* commitFont;

Commit::Commit(const git::Commit& c, QWidget* parent) : commit(c) {
	this->setParent(parent);

	if (commitFont == nullptr) {
		// TODO: Fetch font from config file.
		// NOTE: We do not free the font as it will be cleaned up when application quits.
		commitFont = new QFont("Consolas");
	}

	setFont(*commitFont);

	auto* layout = new QVBoxLayout(this);
	layout->setMargin(0);
	layout->setSpacing(1);
	this->setLayout(layout);

	button = new QPushButton(this);
	button->setFlat(true);
	layout->addWidget(button);

	auto* hLayout = new QHBoxLayout(this);
	hLayout->setMargin(0);
	hLayout->setSpacing(10);
	button->setLayout(hLayout);

	message = new QLabel(this);
	author	= new QLabel(this);
	hash	= new QLabel(this);
	date	= new QLabel(this);

	author->setFixedWidth(100);
	hash->setFixedWidth(45);
	date->setFixedWidth(170);

	auto* spacer = new QSpacerItem(60, 0, QSizePolicy::Expanding);

	hLayout->addWidget(message, 0, Qt::AlignTop);
	hLayout->addSpacerItem(spacer);
	hLayout->addWidget(author, 0, Qt::AlignTop);
	hLayout->addSpacing(10);
	hLayout->addWidget(hash, 0, Qt::AlignTop);
	hLayout->addSpacing(10);
	hLayout->addWidget(date, 0, Qt::AlignTop);
	hLayout->addSpacing(1);

	Setup();
	show();
}

void Commit::Setup() {
	message->setText(commit.GetMessage().c_str());
	author->setText(commit.GetAuthor().c_str());
	hash->setText(commit.GetHash().substr(0, 7).c_str());
	date->setText(commit.GetDate().c_str());
}

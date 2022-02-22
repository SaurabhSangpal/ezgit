#include "Commit.h"

#include <QLabel>
#include <QLayout>
#include <QPushButton>

#include "../git_wrapper/Commit.h"

Commit::Commit(const git::Commit& c, QWidget* parent) : commit(c) {
	this->setParent(parent);

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
	hash->setFixedWidth(40);
	date->setFixedWidth(170);

	auto* spacer = new QSpacerItem(60, 0, QSizePolicy::Expanding);

	hLayout->addWidget(message, 0, Qt::AlignTop);
	hLayout->addSpacerItem(spacer);
	hLayout->addWidget(author, 0, Qt::AlignTop);
	hLayout->addSpacing(10);
	hLayout->addWidget(hash, 0, Qt::AlignTop);
	hLayout->addSpacing(10);
	hLayout->addWidget(date, 0, Qt::AlignTop);
	hLayout->addSpacing(5);

	Setup(commit);

	show();
}

void Commit::Setup(const git::Commit& commit) {
	message->setText(commit.GetMessage().c_str());
	author->setText(commit.GetAuthor().c_str());
	hash->setText(commit.GetHash().c_str());
	date->setText(commit.GetDate().c_str());
}

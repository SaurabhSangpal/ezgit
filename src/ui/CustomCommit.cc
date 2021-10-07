#include "CustomCommit.h"

#include <QLabel>
#include <QLayout>
#include <QPushButton>
#include <QSpacerItem>

#include "../git_wrapper/Commit.h"

CustomCommit::CustomCommit(QWidget* parent) {
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

	auto* spacer = new QSpacerItem(60, 0, QSizePolicy::Expanding);

	hLayout->addWidget(message);
	hLayout->addSpacerItem(spacer);
	hLayout->addWidget(author);
	hLayout->addWidget(hash);
	hLayout->addWidget(date);

	show();
}

void CustomCommit::Setup(const git::Commit& commit) {
	message->setText(commit.GetMessage().c_str());
	author->setText(commit.GetAuthor().c_str());
	hash->setText(commit.GetHash().c_str());
	date->setText(commit.GetDate().c_str());
}

#include "Commit.h"

#include <QPushButton>

#include "../git_wrapper/Commit.h"
#include "./ui_Commit.h"

Commit::Commit(QWidget* parent) : QWidget(parent), ui(new Ui::Commit) {
	ui->setupUi(this);
	auto* btn = new QPushButton(this);
	btn->setFlat(true);
	btn->resize(this->size());
}

void Commit::Setup(const git::Commit& commit) noexcept {
	ui->msg->setText(commit.GetMessage().c_str());
	ui->author->setText(commit.GetAuthor().c_str());
	ui->hash->setText(commit.GetHash().c_str());
	ui->time->setText(commit.GetDate().c_str());
}
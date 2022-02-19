#pragma once

#include <QWidget>

class QCheckBox;
class QLabel;

namespace git {
class File;
}

class ChangedFile : public QWidget {
	Q_OBJECT;

    public:
	explicit ChangedFile(QWidget* parent = nullptr) noexcept;

	void Setup(const git::File& file) noexcept;

    private:
	QCheckBox* checkBox;
	QLabel*	   prefix;
	QLabel*	   path;
};
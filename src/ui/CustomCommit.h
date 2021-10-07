#pragma once

#include <qwidget.h>

namespace git {
class Commit;
}

class QPushButton;
class QLabel;

class CustomCommit : public QWidget {
	Q_OBJECT

    public:
	explicit CustomCommit(QWidget* parent = nullptr);
	void Setup(const git::Commit& commit);

    private:
	QPushButton* button;
	QLabel *     message, *author, *hash, *date;
};

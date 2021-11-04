#pragma once

#include <qwidget.h>

namespace git {
class Commit;
}

class QPushButton;
class QLabel;

class Commit : public QWidget {
	Q_OBJECT

    public:
	explicit Commit(QWidget* parent = nullptr);
	void Setup(const git::Commit& commit);

    private:
	QPushButton* button;
	QLabel *     message, *author, *hash, *date;
};

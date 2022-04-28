#pragma once

#include <QWidget>

namespace git {
class Commit;
}

class QPushButton;
class QLabel;

class Commit : public QWidget {
	Q_OBJECT

    public:
	explicit Commit(const git::Commit& c, QWidget* parent = nullptr);
	void Setup();

	std::string& GetBody() const;

    private:
	QPushButton* button;
	QLabel *     message, *author, *hash, *date;

	const git::Commit& commit;
};

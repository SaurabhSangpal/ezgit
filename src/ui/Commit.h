#pragma once
#include <qwidget.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class Commit;
}
QT_END_NAMESPACE

namespace git {
class Commit;
}

class Commit : public QWidget {
    public:
	explicit Commit(QWidget* parent = nullptr);

	void Setup(const git::Commit& commit) noexcept;

    private:
	Ui::Commit* ui;
};
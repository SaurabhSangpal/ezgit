#pragma once

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class AllCommits;
}
QT_END_NAMESPACE

class AllCommits : public QWidget {
	Q_OBJECT

    public:
	explicit AllCommits(QWidget* parent = nullptr);
	~AllCommits() override;

    private:
	Ui::AllCommits* ui;
};

#pragma once
#include <qwidget.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class RepoViewerWidget;
}
QT_END_NAMESPACE

class RepoViewerWidget : public QWidget {
    public:
	explicit RepoViewerWidget(QWidget* parent = nullptr);
	~RepoViewerWidget() noexcept;

    private:
	Ui::RepoViewerWidget* ui;
};
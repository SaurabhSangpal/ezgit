#pragma once
#include <QMainWindow.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class QWidget;

class MainWindow : public QMainWindow {
    public:
	explicit MainWindow(QWidget* parent = nullptr);
	~MainWindow() noexcept;

    private:
	Ui::MainWindow* ui;

	void OpenRepository() noexcept;
	void InitRepository() noexcept;
	void CloneRepository() noexcept;
};

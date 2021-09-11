#pragma once
#include <QMainWindow.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    public:
	explicit MainWindow(QWidget* parent = nullptr);
	virtual ~MainWindow() = default;

    private:
	Ui::MainWindow* ui;
};

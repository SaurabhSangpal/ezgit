#pragma once
#include <QMainWindow>

#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace git {
class Repository;
}

class QWidget;

class MainWindow : public QMainWindow {
    public:
	explicit MainWindow(QWidget* parent = nullptr);
	~MainWindow() noexcept override;

    private:
	void OpenRepository() noexcept;
	void InitRepository() noexcept;
	void CloneRepository() noexcept;
	void ShowAbout() noexcept;

	void InitializeRepoViewerWidget() noexcept;

	Ui::MainWindow*			 ui;
	std::shared_ptr<git::Repository> repository;
};

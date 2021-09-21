#pragma once

#include <qdialog.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class CloneDialog;
}
QT_END_NAMESPACE

class CloneDialog : public QDialog {
    public:
	explicit CloneDialog(QWidget* parent = nullptr);

    private:
	void BrowseForDestinationFolder() noexcept;

	Ui::CloneDialog* ui;
};
#ifndef GUI_HPP
#define GUI_HPP

#include <QMainWindow>

namespace Ui {
	class gui;
}

class gui : public QMainWindow
{
	Q_OBJECT

public:
	explicit gui(QWidget *parent = 0);
	~gui();

private:
	Ui::gui *ui;
};

#endif // GUI_HPP

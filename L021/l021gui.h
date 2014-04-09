#ifndef L021GUI_H
#define L021GUI_H

#include <QtWidgets/QMainWindow>
#include "ui_l021gui.h"

class L021GUI : public QMainWindow
{
	Q_OBJECT

public:
	L021GUI(QWidget *parent = 0);
	~L021GUI();

private:
	Ui::L021GUIClass ui;
};

#endif // L021GUI_H

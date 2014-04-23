#ifndef L021GUI_H
#define L021GUI_H

#include <QtWidgets/QMainWindow>
#include "ui_l021gui.h"
#include "UVDialog.h"
#include "UV.hpp"

class L021GUI : public QMainWindow
{
	Q_OBJECT

public:
	L021GUI(QWidget *parent = 0);
	~L021GUI();

private slots:
	void AddUv();
	void EditUv();
private:
	Ui::gui ui;
};

#endif // L021GUI_H

#pragma once
#include <qdialog.h>
#include "ui_equiv_dialog.h"
#include "UV.hpp"
class EquivDialog :
	public Ui::equiv_dialog,
	public QDialog
{
public:
	EquivDialog(QWidget* parent);
	~EquivDialog();
	static void ShowDialog(int* equiv, QWidget* parent = nullptr);
};
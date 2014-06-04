#ifndef L021GUI_H
#define L021GUI_H

#include <QtWidgets/QMainWindow>
#include <qmessagebox.h>
#include "ui_l021gui.h"
#include "ui_main_window.h"
#include "UVDialog.h"
#include "UVList.h"
#include "CursusList.h"
#include "UV.hpp"
#include "AllUtility.h"
#include "UTProfiler.h"

class L021GUI : public QMainWindow
{
	Q_OBJECT

public:
	L021GUI(QWidget *parent = 0);
	~L021GUI();

private slots:
	void AddUv();
	void EditUv();
	void RemoveUV();

	void AddCursus_Dossier();
	void RemoveCursus_Dossier();

	void AddSemestre_Dossier();
	void RemoveSemestre_Dossier();

	void AddUV_Semestre();
	void RemoveUV_Semestre();
private:
	Ui::MainWindow ui;
	void UVListChanged();
	void CursusList_DossierChanged();
	void UVList_DossierChanged();
};

#endif // L021GUI_H

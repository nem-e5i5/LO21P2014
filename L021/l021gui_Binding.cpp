#include "l021gui.h"

L021GUI::L021GUI(QWidget *parent)
: QMainWindow(parent)
{
	ui.setupUi(this);
	QObject::connect(ui.add_uv_button, SIGNAL(clicked()), this, SLOT(AddUv()));
	QObject::connect(ui.modifie_uv_button, SIGNAL(clicked()), this, SLOT(EditUv()));
	QObject::connect(ui.remove_uv_button, SIGNAL(clicked()), this, SLOT(RemoveUV()));
	
	QObject::connect(ui.equivalence_button, SIGNAL(clicked()), this, SLOT(EditEquiv_Dossier()));

	QObject::connect(ui.add_cursus_to_dossier_button, SIGNAL(clicked()), this, SLOT(AddCursus_Dossier()));
	QObject::connect(ui.remove_cursus_from_dossier_button, SIGNAL(clicked()), this, SLOT(RemoveCursus_Dossier()));
	
	QObject::connect(ui.add_uv_to_dossier_button, SIGNAL(clicked()), this, SLOT(AddUV_Semestre()));
	QObject::connect(ui.remove_uv_from_dossier_button, SIGNAL(clicked()), this, SLOT(RemoveUV_Semestre()));
	
	QObject::connect(ui.add_semestre_button, SIGNAL(clicked()), this, SLOT(AddSemestre_Dossier()));
	QObject::connect(ui.remove_semestre_button, SIGNAL(clicked()), this, SLOT(RemoveSemestre_Dossier()));

	
	UVListChanged();
	CursusList_DossierChanged();
	UVList_DossierChanged();
}

L021GUI::~L021GUI()
{

}
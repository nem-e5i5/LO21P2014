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
	
	QObject::connect(ui.modify_status, SIGNAL(clicked()), this, SLOT(ChangeStatus()));

	QObject::connect(ui.add_semestre_button, SIGNAL(clicked()), this, SLOT(AddSemestre_Dossier()));
	QObject::connect(ui.remove_semestre_button, SIGNAL(clicked()), this, SLOT(RemoveSemestre_Dossier()));

	QObject::connect(ui.add_cursus_button, SIGNAL(clicked()), this, SLOT(AddCursus()));
	QObject::connect(ui.modifie_cursus_button, SIGNAL(clicked()), this, SLOT(EditCursus()));
	QObject::connect(ui.remove_cursus_button, SIGNAL(clicked()), this, SLOT(RemoveCursus()));

	QObject::connect(ui.actionEnregistrer, SIGNAL(triggered()), this, SLOT(SaveDossier()));
	QObject::connect(ui.actionTexte, SIGNAL(triggered()), this, SLOT(ImportUV()));
	QObject::connect(ui.actionAutre_dossier, SIGNAL(triggered()), this, SLOT(LoadUV()));
	QObject::connect(ui.actionCharger, SIGNAL(triggered()), this, SLOT(LoadDossier()));

	QObject::connect(ui.autocomplete_button, SIGNAL(clicked()), this, SLOT(AutoComplete()));

	UVListChanged();
	CursusList_DossierChanged();
	UVList_DossierChanged();
	CursusListChanged();
}

L021GUI::~L021GUI()
{

}
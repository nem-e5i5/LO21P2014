#pragma once
#include <qdialog.h>
#include "ui_semestre_status_dialog.h"
#include "UV.hpp"
#include "Semestre.h"
class SemestreStatusDialog :
	public QDialog,
	public Ui::semestre_status_dialog
{
public:
	SemestreStatusDialog(QWidget* parent);
	~SemestreStatusDialog();
	// Affiche une bo�te de dialogue avec les informations de l'UV pass� en param�tre, cette UV est �dit� par l'utilisateur. Retourne la r�f�rence pass� en param�tre
	static SemestreSuivi& ShowDialog(SemestreSuivi& SS, QWidget* parent = nullptr);
};
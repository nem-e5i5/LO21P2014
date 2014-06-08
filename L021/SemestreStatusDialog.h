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
	// Affiche une boîte de dialogue avec les informations de l'UV passé en paramètre, cette UV est édité par l'utilisateur. Retourne la référence passé en paramètre
	static SemestreSuivi& ShowDialog(SemestreSuivi& SS, QWidget* parent = nullptr);
};
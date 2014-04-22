#pragma once
#include "ui_AddUV.h"
#include "UV.h"

class AddUVDialog :
	public Ui::DialogUV
{
public:
	AddUVDialog();
	~AddUVDialog();
	// Affiche une boîte de dialogue de création d'UV, retourne l'UV saisie ou bien UV::null si rien n'est saisie
	static UV ShowDialog();
};


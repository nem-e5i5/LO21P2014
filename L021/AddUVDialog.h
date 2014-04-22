#pragma once
#include <qdialog.h>
#include "ui_AddUV.h"
#include "UV.hpp"

class AddUVDialog :
	public Ui::DialogUV,
	public QDialog
{
public:
	AddUVDialog(QWidget* parent);
	~AddUVDialog();
	// Affiche une boîte de dialogue de création d'UV, retourne l'UV saisie ou bien UV::null si rien n'est saisie
	static UV ShowDialog(QWidget* parent = nullptr);
};


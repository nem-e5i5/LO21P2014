#pragma once
#include <qdialog.h>
#include <qscrollarea.h>
#include "ui_validator_dialog.h"
#include "Cursus.h"
class ValidatorDialog :
	public Ui::Validator_dialog,
	public QDialog
{
public:
	ValidatorDialog(QWidget* parent);
	~ValidatorDialog();
	// Affiche une bo�te de dialogue avec les informations de l'UV pass� en param�tre, cette UV est �dit� par l'utilisateur. Retourne la r�f�rence pass� en param�tre
	static Cursus& ShowDialog(Cursus& cr, QWidget* parent = nullptr);
	static Cursus ShowDialog(QWidget* parent = nullptr);

	void AjouterLigne();
	void RetirerLigne();
};
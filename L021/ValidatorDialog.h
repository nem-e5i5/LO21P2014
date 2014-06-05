#pragma once
#include <qdialog.h>
#include <qscrollarea.h>
#include "ui_validator_dialog.h"
#include "Cursus.h"
#include <vector>
class ValidatorDialog :
	public Ui::Validator_dialog,
	public QDialog
{
private:
	vector<vector<QWidget*>> widget_list;
public:
	ValidatorDialog(QWidget* parent);
	~ValidatorDialog();
	// Affiche une boîte de dialogue avec les informations de l'UV passé en paramètre, cette UV est édité par l'utilisateur. Retourne la référence passé en paramètre
	/*static Cursus& ShowDialog(Cursus& cr, QWidget* parent = nullptr);
	static Cursus ShowDialog(QWidget* parent = nullptr);*/
private slots:
	void AjouterLigne();
	void RetirerLigne();
};
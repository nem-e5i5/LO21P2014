#pragma once
#include <qobject.h>
#include <qdialog.h>
#include <qscrollarea.h>
#include "ui_validator_dialog.h"
#include "Cursus.h"
#include <vector>
#include <QSpinBox>
#include <qlineedit.h>
#include <qbuffer.h>
#include <qcombobox.h>
#include "UTProfiler.h"
#include <qcheckbox.h>

class ValidatorDialog :
	public QDialog,
	public Ui::Validator_dialog
	
{
	Q_OBJECT
private:
	vector<vector<QWidget*>> widget_list;
	/// <summary>Cette fonction retourne un pointeur qu'il faudra delete vous même</summary>
	QBuffer* ParseFormData();
public:
	ValidatorDialog(QWidget* parent);
	~ValidatorDialog();
	/// <summary>Cette fonction retourne un pointeur qu'il faudra delete vous même</summary>
	static CursusValidator* ShowDialog(CursusValidator* cr, QWidget* parent = nullptr);
	/// <summary>Cette fonction retourne un pointeur qu'il faudra delete vous même</summary>
	static CursusValidator* ShowDialog(QWidget* parent = nullptr);
public slots:
	void AjouterLigne();
	void RetirerLigne();
	void ComboChanged(QString s, QObject* sender = nullptr);

	void TextFocusLost(QObject* send = nullptr);
	void TextFocusLost2(QObject* send = nullptr);

};
#include "ValidatorDialog.h"

ValidatorDialog::ValidatorDialog(QWidget* parent)
{
	widget_list={};
	setupUi(this);
}
ValidatorDialog::~ValidatorDialog()
{

}


QBuffer* ValidatorDialog::ParseFormData()
{
	QBuffer* ret = new QBuffer();
	ret->open(QIODevice::ReadWrite);
	QDataStream dst(ret);
	QString vname = this->choose_validator_combobox->currentText();
	dst << vname;
	for (auto i : widget_list)
	{
		auto type = dynamic_cast<QComboBox*>(i[0])->currentText();
		if (type == "int")
		{
			auto* item = dynamic_cast<QSpinBox*>(i[1]);
			dst << item->value();
		}
	}
	ret->seek(0);
	return ret;
}

CursusValidator* ValidatorDialog::ShowDialog(CursusValidator* cr, QWidget* parent)
{
	//TODO, non vital pour avoir une appli fonctionnelle
	return cr;
}
CursusValidator* ValidatorDialog::ShowDialog(QWidget* parent)
{
	ValidatorDialog x(parent);
	auto v = Select < pair<QString, const ValidatorFactory*>, QString>
		(CursusValidator::Validators.begin(), CursusValidator::Validators.end(), 
		[](const pair<QString, const ValidatorFactory*>& x) { return x.first; });

	x.choose_validator_combobox->addItems(
		QStringList::fromVector( //on en reparle
			QVector<QString>::fromStdVector( //de toute ces
				toVector<QString>(v, v.getEnd())))); //conversions???
	QObject::connect(x.add_button, SIGNAL(clicked()), &x, SLOT(AjouterLigne()));
	int rflag = x.exec();
	if (rflag == 0)
		return nullptr;
	else
	{
		auto* buff = x.ParseFormData();
		QDataStream stream(buff);
		auto* ret = CursusValidator::true_UnSerialize(stream); //Une erreur ici ? RTFM!
		buff->close();
		delete buff;
		return ret;
	}
}

void ValidatorDialog::AjouterLigne() {
	static const QStringList combo_options = {"int", "string", "UV", "bool", "UVType", "UVStatus", "Cursus"};

	QComboBox* combo= new(QComboBox);
	combo->addItems(combo_options);
	widget_list.push_back({combo, nullptr});
	formLayout_2->setWidget(widget_list.size() -1, QFormLayout::ItemRole::LabelRole, combo);
	combo->show();
	QObject::connect(combo, SIGNAL(currentTextChanged(QString)), this, SLOT(ComboChanged(QString)));
	ComboChanged(combo_options[0], combo);
}

void ValidatorDialog::ComboChanged(QString s, QObject* sender) {
	if (sender == nullptr) sender=QObject::sender();
	for (int i=0; i<widget_list.size(); i++) {
		if (widget_list[i][0]==sender) {
			if (widget_list[i][1] != nullptr)
			{
				widget_list[i][1]->hide();
				formLayout_2->removeWidget(widget_list[i][1]);
				delete widget_list[i][1];
				widget_list[i][1] = nullptr;
			}
			// remove from form_layout2
			if (s=="int") {
				widget_list[i][1]= new QSpinBox;
				formLayout_2->setWidget(i, QFormLayout::ItemRole::FieldRole, widget_list[i][1]);
				widget_list[i][1]->show();
			}

			return;
		}
	}
}

void ValidatorDialog::RetirerLigne() {

}

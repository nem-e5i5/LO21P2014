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
		else if (type == "string" || type == "UV" || type == "Cursus")
		{
			auto* item = dynamic_cast<QLineEdit*>(i[1]);
			dst << item->text();
		}
		else if (type == "UVType" || type == "UVStatus")
		{
			auto* item = dynamic_cast<QComboBox*>(i[1]);
			if (type == "UVType") dst << UVTypeFromName(item->currentText());
			else dst << UVStatusFromName(item->currentText());
		}
		else if (type == "bool")
		{
			auto* item = dynamic_cast<QCheckBox*>(i[1]);
			dst << item->isChecked();
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
	QObject::connect(x.remove_button, SIGNAL(clicked()), &x, SLOT(RetirerLigne()));
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
				return;
			}
			if (s == "string" || s == "UV" || s == "Cursus") {
				widget_list[i][1] = new QLineEdit(nullptr);
				formLayout_2->setWidget(i, QFormLayout::ItemRole::FieldRole, widget_list[i][1]);
				if (s == "UV") QObject::connect(widget_list[i][1], SIGNAL(editingFinished()), this, SLOT(TextFocusLost()));
				if (s == "Cursus") QObject::connect(widget_list[i][1], SIGNAL(editingFinished()), this, SLOT(TextFocusLost2()));
				widget_list[i][1]->show();
				return;
			}
			if (s == "UVType" || s == "UVStatus") {
				auto* cb = new QComboBox();
				if (s == "UVType") {
					cb->addItem("Mixe");
					for (int i = 0; i < UVType::size; ++i) cb->addItem(UVTypeName(static_cast<UVType>(i)));
				}
				else for (int i = 0; i < UVStatus::Usize; ++i) cb->addItem(UVStatusName(static_cast<UVStatus>(i)));
				widget_list[i][1] = cb;
				formLayout_2->setWidget(i, QFormLayout::ItemRole::FieldRole, widget_list[i][1]);
				widget_list[i][1]->show();
				return;
			}
			if (s == "bool")
			{
				widget_list[i][1] = new QCheckBox;
				formLayout_2->setWidget(i, QFormLayout::ItemRole::FieldRole, widget_list[i][1]);
				if (s == "UV") QObject::connect(widget_list[i][1], SIGNAL(editingFinished()), this, SLOT(TextFocusLost()));
				widget_list[i][1]->show();
				return;
			}

			return;
		}
	}
}

void ValidatorDialog::TextFocusLost(QObject* sender)
{
	static map<QObject*, QString> toldya;
	if (sender == nullptr) sender = QObject::sender();
	auto* o = dynamic_cast<QLineEdit*>(sender);
	if (!UTProfiler::GetInstance()->UVExists(o->text()) && toldya[sender] != o->text())
	{
		Notify("Attention: L'UV " + o->text() + QString::fromWCharArray(L" n'est pas enregistré, ceci peut être causé par une faute de frappe"));
		toldya[sender] = o->text();
	}
}

void ValidatorDialog::TextFocusLost2(QObject* sender)
{
	static map<QObject*, QString> toldya;
	if (sender == nullptr) sender = QObject::sender();
	auto* o = dynamic_cast<QLineEdit*>(sender);
	if (!UTProfiler::GetInstance()->CursusExists(o->text()) && toldya[sender] != o->text())
	{
		Notify("Attention: Le cursus " + o->text() + QString::fromWCharArray(L" n'est pas enregistré, ceci peut être causé par une faute de frappe"));
		toldya[sender] = o->text();
	}
}

void ValidatorDialog::RetirerLigne() {
	if (widget_list.size() <= 0) return;
	auto& item = *(widget_list.end() - 1);
	if (item.at(0) != nullptr)
	{
		formLayout_2->removeWidget(item.at(0));
		delete item.at(0);
	}
	if (item.at(1) != nullptr)
	{
		formLayout_2->removeWidget(item.at(1));
		delete item.at(1);
	}
	widget_list.pop_back();
}

#include "l021gui.h"

void L021GUI::EditEquiv_Dossier()
{
	auto& dossier = UTProfiler::GetInstance()->getDossier();
	int equiv[UVType::size];
	for (int i = 0; i < UVType::size; ++i) equiv[i] = dossier.getNbEquivalences(static_cast<UVType>(i));
	EquivDialog::ShowDialog(equiv);
	for (int i = 0; i < UVType::size; ++i) dossier.setNbEquivalences(static_cast<UVType>(i), equiv[i]);
	CursusList_DossierChanged();
}

void L021GUI::AddCursus_Dossier()
{
	auto xiter = UTProfiler::GetInstance()->CursusIterator();
	auto viter = UTProfiler::GetInstance()->getDossier().CursusIterator();
	auto iter = Where<Cursus>(xiter, xiter.getEnd(), 
		[viter](const Cursus& x) 
		{ 
			return Where<Cursus>(viter, viter.getEnd(), 
				[&x](const Cursus& y)
				{
					return x.getName() == y.getName();
				}).ended();
		});
	QString t = CursusList::ShowDialog(iter, iter.getEnd());
	if (t != "")
	{
		UTProfiler::GetInstance()->getDossier().InscriptionCursus(t);
		CursusList_DossierChanged();
	}
	else Notify(L"Action annulée");
}

void L021GUI::RemoveCursus_Dossier()
{
	if (ui.dossier_cursus_list->selectedItems().size() > 0)
	{
		QString t = ui.dossier_cursus_list->selectedItems()[0]->text();
		UTProfiler::GetInstance()->getDossier().DesinscriptionCursusByName(t);
		CursusList_DossierChanged();
	}
	else Notify(L"Pas de cursus choisi");
}

void L021GUI::AddSemestre_Dossier()
{
	if (ui.dossier_uv_list->topLevelItemCount() > 0)
	{
		UTProfiler::GetInstance()->getDossier().NouveauSemestre(static_cast<Semestre>(!
			UTProfiler::GetInstance()->getDossier().SemestreRef(
			ui.dossier_uv_list->topLevelItem(ui.dossier_uv_list->topLevelItemCount() - 1)->text(0)
			).get_Saison()));
	}
	else UTProfiler::GetInstance()->getDossier().NouveauSemestre();
	UVList_DossierChanged();
}
void L021GUI::RemoveSemestre_Dossier()
{
	if (ui.dossier_uv_list->selectedItems().size() <= 0)
	{
		Notify(L"Pas de semestre choisi");
		return;
	}
	auto p = ui.dossier_uv_list->selectedItems().at(0)->parent();
	if (p == nullptr) p = ui.dossier_uv_list->selectedItems().at(0);
	
	auto* sem = &UTProfiler::GetInstance()->getDossier().SemestreRef(p->text(0));
	auto* last = &UTProfiler::GetInstance()->getDossier().SemestreRef();
	if (sem != last)
	{
		auto iter = sem->UVIterator();
		for (; !iter.ended(); ++iter)
			sem->Desinscription((*iter).get_uv().get_code());
		for (int i = 0; i < UVType::size; ++i)
			sem->set_Prevision(static_cast<UVType>(i), 0);
		sem->set_ALEtranger(false);
		sem->set_Status(SemestreStatus::PR);
	}
	else UTProfiler::GetInstance()->getDossier().SupprimerSemestre(p->text(0));
	UVList_DossierChanged();
}

void L021GUI::AddUV_Semestre()
{
	if (ui.dossier_uv_list->selectedItems().size() <= 0)
	{
		Notify(L"Pas de semestre choisi");
		return;
	}

	auto p = ui.dossier_uv_list->selectedItems().at(0)->parent();
	if (p == nullptr) p = ui.dossier_uv_list->selectedItems().at(0);

	auto s = UTProfiler::GetInstance()->getDossier().SemestreRef(p->text(0));
	auto iter = UTProfiler::GetInstance()->getDossier().UVPrenableIterator(p->text(0));
	QString t = UVList::ShowDialog(iter, iter.getEnd());
	if (t != "")
	{
		UTProfiler::GetInstance()->getDossier()
			.SemestreRef(p->text(0))
			.Inscription(UVEncours(t, UVStatus::EC));
		UVList_DossierChanged();
	}
	else Notify(L"Action annulée");
	
}
void L021GUI::RemoveUV_Semestre()
{
	if (ui.dossier_uv_list->selectedItems().size() <= 0)
	{
		Notify(L"Pas d'UV choisi");
		return;
	}
	auto p = ui.dossier_uv_list->selectedItems().at(0)->parent();
	if (p == nullptr)
	{
		Notify(L"Sélectionnez une UV du semestre (pas le semestre entier)");
		return;
	}
	UTProfiler::GetInstance()->getDossier()
		.SemestreRef(p->text(0))
		.Desinscription(ui.dossier_uv_list->selectedItems().at(0)->text(0));
	UVList_DossierChanged();
}

void L021GUI::ChangeStatus()
{
	if (ui.dossier_uv_list->selectedItems().size() <= 0)
	{
		Notify(L"Rien de sélectionné");
		return;
	}
	auto p = ui.dossier_uv_list->selectedItems().at(0);
	if (p->parent() == nullptr)
	{
		auto& s = UTProfiler::GetInstance()->getDossier()
			.SemestreRef(p->text(0));
		SemestreStatusDialog::ShowDialog(s);
		UVList_DossierChanged();
	}
	else
	{
		auto& s = UTProfiler::GetInstance()->getDossier()
			.SemestreRef(p->parent()->text(0)).UVRef(p->text(0));
		s.set_status((static_cast<UVStatus>((s.get_status() + 1) % UVStatus::Usize)));
		p->setText(2, UVStatusName(s.get_status()));
	}
	CursusList_DossierChanged();
}

void L021GUI::CursusList_DossierChanged()
{
	ui.dossier_cursus_list->clearContents();
	auto iter = UTProfiler::GetInstance()->getDossier().CursusIterator();
	for (int i = 0; !iter.ended(); ++iter)
	{
		ui.dossier_cursus_list->setRowCount(i + 1);
		ui.dossier_cursus_list->setItem(i, 0, new QTableWidgetItem((*iter).getName()));
		ui.dossier_cursus_list->setItem(i, 1, new QTableWidgetItem((*iter).Validate(UTProfiler::GetInstance()->getDossier()) ? "Oui": "Non"));
		ui.dossier_cursus_list->setItem(i, 2, new QTableWidgetItem((*iter).MayValidate(UTProfiler::GetInstance()->getDossier()) ? "Oui" : "Non"));
		++i;
	}
}

void L021GUI::UVList_DossierChanged()
{
	ui.dossier_uv_list->clear();
	auto iter = UTProfiler::GetInstance()->getDossier().SemestreIterator();
	for (int i = 0; !iter.ended(); ++iter)
	{
		auto twid = new QTreeWidgetItem(ui.dossier_uv_list);
		twid->setText(0, 
			QString((*iter).get_Saison() == Semestre::Automne ? "A" : "P") + 
			QString::number(i / 2 + 1));
		twid->setText(1, QString::number((*iter).get_nb_credit_previsional(UVType::Mixe)));
		twid->setText(2, SemestreStatusName((*iter).get_Status()));
		auto iter2 = (*iter).UVIterator();
		for (int j = 0; !iter2.ended(); ++iter2)
		{
			auto twid2 = new QTreeWidgetItem(twid);
			twid2->setText(0, (*iter2).get_uv().get_code());
			twid2->setText(1, QString::number((*iter2).get_uv().get_nb_credit(UVType::Mixe)));
			twid2->setText(2, UVStatusName((*iter2).get_status()));
			twid->addChild(twid2);
			++j;
		}
		ui.dossier_uv_list->addTopLevelItem(twid);
		++i;
	}
}
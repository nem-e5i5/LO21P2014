#include "l021gui.h"

void L021GUI::SaveDossier()
{
	auto fname = QFileDialog::getSaveFileName(
		nullptr,
		"Enregistrer sous...",
		"",
		"fichier binaire (*.bin)");

	if (fname != "") UTProfiler::GetInstance()->AppToBinFile(fname);
}

void L021GUI::LoadDossier()
{
	auto fname = QFileDialog::getOpenFileName(
		nullptr,
		"Ouvrir...",
		"",
		"fichier binaire (*.bin)");
	if (fname != "")
	{
		UTProfiler::GetInstance()->ResetInstance();
		UTProfiler::GetInstance()->BinFileToApp(fname);
		UVListChanged();
		CursusListChanged();
		CursusList_DossierChanged();
		UVList_DossierChanged();
	}
}

void L021GUI::LoadUV()
{
	auto fname = QFileDialog::getOpenFileName(
		nullptr,
		"Ouvrir...",
		"",
		"fichier binaire (*.bin)");

	if (fname != "")
	{
		UTProfiler::GetInstance()->ImportUVOnly(fname);
		UVListChanged();
		CursusListChanged();
		CursusList_DossierChanged();
		UVList_DossierChanged();
	}
}

void L021GUI::ImportUV()
{
	auto fname = QFileDialog::getOpenFileName(
		nullptr,
		"Ouvrir...",
		"",
		"fichier texte (*.txt)");

	if (fname != "")
	{
		UTProfiler::GetInstance()->ImportUVOnlytxt(fname);
		UVListChanged();
		CursusListChanged();
		CursusList_DossierChanged();
		UVList_DossierChanged();
	}
}

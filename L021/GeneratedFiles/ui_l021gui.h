/********************************************************************************
** Form generated from reading UI file 'l021gui.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_L021GUI_H
#define UI_L021GUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_L021GUIClass
{
public:
    QAction *actionSaisir_dossier;
    QAction *actionNouveau;
    QAction *actionOuvrir;
    QAction *actionEnregistrer;
    QAction *actionEnregistrer_sous;
    QAction *actionAjouter;
    QAction *actionModifier;
    QAction *actionOuvrir_2;
    QAction *actionTexte;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menuUV_2;
    QMenu *menuImporter;
    QMenu *menuDossier_2;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(282, 231);
        actionSaisir_dossier = new QAction(MainWindow);
        actionSaisir_dossier->setObjectName(QStringLiteral("actionSaisir_dossier"));
        actionNouveau = new QAction(MainWindow);
        actionNouveau->setObjectName(QStringLiteral("actionNouveau"));
        actionOuvrir = new QAction(MainWindow);
        actionOuvrir->setObjectName(QStringLiteral("actionOuvrir"));
        actionEnregistrer = new QAction(MainWindow);
        actionEnregistrer->setObjectName(QStringLiteral("actionEnregistrer"));
        actionEnregistrer_sous = new QAction(MainWindow);
        actionEnregistrer_sous->setObjectName(QStringLiteral("actionEnregistrer_sous"));
        actionAjouter = new QAction(MainWindow);
        actionAjouter->setObjectName(QStringLiteral("actionAjouter"));
        actionModifier = new QAction(MainWindow);
        actionModifier->setObjectName(QStringLiteral("actionModifier"));
        actionOuvrir_2 = new QAction(MainWindow);
        actionOuvrir_2->setObjectName(QStringLiteral("actionOuvrir_2"));
        actionTexte = new QAction(MainWindow);
        actionTexte->setObjectName(QStringLiteral("actionTexte"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 282, 21));
        menuUV_2 = new QMenu(menubar);
        menuUV_2->setObjectName(QStringLiteral("menuUV_2"));
        menuImporter = new QMenu(menuUV_2);
        menuImporter->setObjectName(QStringLiteral("menuImporter"));
        menuDossier_2 = new QMenu(menubar);
        menuDossier_2->setObjectName(QStringLiteral("menuDossier_2"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuUV_2->menuAction());
        menubar->addAction(menuDossier_2->menuAction());
        menuUV_2->addAction(actionAjouter);
        menuUV_2->addAction(actionModifier);
        menuUV_2->addAction(actionOuvrir_2);
        menuUV_2->addAction(menuImporter->menuAction());
        menuImporter->addAction(actionTexte);
        menuDossier_2->addAction(actionNouveau);
        menuDossier_2->addAction(actionOuvrir);
        menuDossier_2->addAction(actionEnregistrer);
        menuDossier_2->addAction(actionEnregistrer_sous);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("L021GUIClass", "MainWindow", 0));
        actionSaisir_dossier->setText(QApplication::translate("L021GUIClass", "Saisir dossier", 0));
        actionNouveau->setText(QApplication::translate("L021GUIClass", "Nouveau", 0));
        actionOuvrir->setText(QApplication::translate("L021GUIClass", "Ouvrir...", 0));
        actionEnregistrer->setText(QApplication::translate("L021GUIClass", "Enregistrer", 0));
        actionEnregistrer_sous->setText(QApplication::translate("L021GUIClass", "Enregistrer sous...", 0));
        actionAjouter->setText(QApplication::translate("L021GUIClass", "Liste", 0));
        actionModifier->setText(QApplication::translate("L021GUIClass", "Ajouter...", 0));
        actionOuvrir_2->setText(QApplication::translate("L021GUIClass", "Ouvrir...", 0));
        actionTexte->setText(QApplication::translate("L021GUIClass", "Texte...", 0));
        menuUV_2->setTitle(QApplication::translate("L021GUIClass", "UV", 0));
        menuImporter->setTitle(QApplication::translate("L021GUIClass", "Importer", 0));
        menuDossier_2->setTitle(QApplication::translate("L021GUIClass", "Dossier", 0));
    } // retranslateUi

};

namespace Ui {
    class L021GUIClass: public Ui_L021GUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_L021GUI_H

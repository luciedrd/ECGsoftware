#include "form_patient.h"
#include "ui_form_patient.h"
#include <QFile>
#include <QTextStream>
#include <QtDebug>
#include <qcoreapplication.h>

Form_patient::Form_patient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Form_patient)
{
    ui->setupUi(this);
    QPushButton * validerFormulaire = new QPushButton("Valider formulaire",ui->ValideFormulaire); // on creer un BP pour creer un fichier.txt
    connect(validerFormulaire, SIGNAL(clicked()), this, SLOT(CreationFormPatient()));

}

void Form_patient::Write(QString Filename) // Write() permet de générer un fichier .txt,
                                            //avec comme contenu la valeur de out
{
    QFile mFile(Filename);

    if(!mFile.open(QFile::WriteOnly | QFile::Text))
    {
        qDebug() << "erreur";
        return;
    }

    QTextStream out(&mFile);

    out <<" Nom : "<< ui->Nom->text() <<"\r\n Prénom : "<< ui->Prenom->text()
       << "\r\n Date de naissance : " << ui->Jour->currentText()
       <<"/"<<ui->Mois->currentText()<<"/"<<ui->Annee->currentText()
      <<"\r\n Taille : "<<ui->Taille->text()
      <<" cm \r\n Poids : "<<ui->Poids->text()<<" Kg";
    // sur le fichier .txt sera écrit toutes les données du out

    mFile.flush();
    mFile.close();
}

void Form_patient::CreationFormPatient(){ // on creer le fichier.txt
    QString mFilename="C:/Users/Lucie Darde/Desktop/myfile.txt";
     Write(mFilename);
     this->close(); //on ferme la fenetre une fois validé


}

Form_patient::~Form_patient()
{
    delete ui;
}

#ifndef FORM_PATIENT_H
#define FORM_PATIENT_H

#include <QDialog>

namespace Ui {
class Form_patient;
}

class Form_patient : public QDialog
{
    Q_OBJECT


public slots:
        void CreationFormPatient();

public:
    explicit Form_patient(QWidget *parent = nullptr);
    ~Form_patient();
    void Write(QString);



private:
    Ui::Form_patient *ui;
};

#endif // FORM_PATIENT_H

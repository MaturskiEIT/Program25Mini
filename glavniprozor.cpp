#include "glavniprozor.h"
#include "ui_glavniprozor.h"
#include "konekcija.h"
#include "profesori.h"
#include "profesorikojiimajumail.h"

GlavniProzor::GlavniProzor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GlavniProzor)
{
    ui->setupUi(this);
}

GlavniProzor::~GlavniProzor()
{
    delete ui;
}

void GlavniProzor::on_actionIzlaz_triggered()
{
    this->close();
}

void GlavniProzor::on_actionProfesori_triggered()
{
    Profesori *p = new Profesori(this);
    p->setModal(true);
    p->show();
}

void GlavniProzor::on_actionProfesori_koji_imaju_mail_triggered()
{
    ProfesoriKojiImajuMail *pm = new ProfesoriKojiImajuMail(this);
    pm->setModal(true);
    pm->show();
}

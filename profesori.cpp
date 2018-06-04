#include "profesori.h"
#include "ui_profesori.h"
#include "konekcija.h"
#include <QMessageBox>

Profesori::Profesori(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Profesori)
{
    ui->setupUi(this);

    Konekcija baza;
    baza.dbOpen();

    QSqlQuery upit;

    upit.prepare("SELECT ProfesorID, Ime, Prezime FROM Profesor ORDER BY ProfesorID;");
    upit.exec();

    QSqlQueryModel *model;
    model = new QSqlQueryModel();
    model->setQuery(upit);
    ui->tableView->setModel(model);

    baza.dbClose();
}

Profesori::~Profesori()
{
    delete ui;
}

void Profesori::on_pushButtonIzadji_clicked()
{
    this->close();
}

void Profesori::on_pushButtonNovi_clicked()
{
    Konekcija baza;
    baza.dbOpen();

    QSqlQuery upit;

    upit.prepare("SELECT MAX(ProfesorID) FROM Profesor;");

    upit.exec();

    upit.next();
    int rb = upit.value(0).isNull()>0?0:upit.value(0).toInt();
    ui->lineEditSifra->setText(QString::number(rb + 1));

    ui->lineEditIme->clear();
    ui->lineEditPrezime->clear();
    ui->lineEditTelefon->clear();
    ui->lineEditMail->clear();
    ui->dateEditDatumRodjenja->setDate(QDate::currentDate());

    upit.prepare("SELECT ProfesorID, Ime, Prezime FROM Profesor ORDER BY ProfesorID;");
    upit.exec();

    QSqlQueryModel *model;
    model = new QSqlQueryModel();
    model->setQuery(upit);
    ui->tableView->setModel(model);

    baza.dbClose();

    ui->lineEditIme->setFocus();
}

void Profesori::on_pushButtonUpisi_clicked()
{
    QString ime = ui->lineEditIme->text();
    QString prezime = ui->lineEditPrezime->text();
    QString datumRodjenja = ui->dateEditDatumRodjenja->date().toString(Qt::TextDate);
    QString telefon = ui->lineEditTelefon->text();
    QString mail = ui->lineEditMail->text();

    Konekcija baza;
    baza.dbOpen();

    QSqlQuery upit;

    if(mail.isEmpty())
    {
        upit.prepare("INSERT INTO Profesor (Ime, Prezime, DatumRodjenja, Telefon) VALUES (:ime, :prezime, :datumRodjenja, :telefon);");
        upit.bindValue(":ime", ime);
        upit.bindValue(":prezime", prezime);
        upit.bindValue(":datumRodjenja", datumRodjenja);
        upit.bindValue(":telefon", telefon);
    }
    else
    {
        upit.prepare("INSERT INTO Profesor (Ime, Prezime, DatumRodjenja, Telefon, E_mail) VALUES (:ime, :prezime, :datumRodjenja, :telefon, :mail);");
        upit.bindValue(":ime", ime);
        upit.bindValue(":prezime", prezime);
        upit.bindValue(":datumRodjenja", datumRodjenja);
        upit.bindValue(":telefon", telefon);
        upit.bindValue(":mail", mail);
    }

    upit.exec();

    QMessageBox::information(this, "Uspesno!!!", "Podaci o profesoru uspesno upisani!!!");

    upit.prepare("SELECT ProfesorID, Ime, Prezime FROM Profesor ORDER BY ProfesorID;");
    upit.exec();

    QSqlQueryModel *model;
    model = new QSqlQueryModel();
    model->setQuery(upit);
    ui->tableView->setModel(model);

    baza.dbClose();
}

void Profesori::on_tableView_doubleClicked(const QModelIndex &index)
{
    int red = index.row();
    QString profesorID = index.sibling(red, 0).data().toString();

    Konekcija baza;
    baza.dbOpen();

    QSqlQuery upit;

    upit.prepare("SELECT Ime, Prezime, DatumRodjenja, Telefon, E_mail FROM Profesor WHERE ProfesorID = :profesorID;");
    upit.bindValue(":profesorID", profesorID);

    upit.exec();

    upit.next();
    ui->lineEditSifra->setText(profesorID);
    ui->lineEditIme->setText(upit.value(0).toString());
    ui->lineEditPrezime->setText(upit.value(1).toString());
    ui->dateEditDatumRodjenja->setDate(QDate::fromString(upit.value(2).toString()));
    ui->lineEditTelefon->setText(upit.value(3).toString());
    ui->lineEditMail->setText(upit.value(4).toString());

    baza.dbClose();
}

void Profesori::on_pushButtonIzmeni_clicked()
{
    QString profesorID = ui->lineEditSifra->text();
    QString ime = ui->lineEditIme->text();
    QString prezime = ui->lineEditPrezime->text();
    QString datumRodjenja = ui->dateEditDatumRodjenja->date().toString(Qt::TextDate);
    QString telefon = ui->lineEditTelefon->text();
    QString mail = ui->lineEditMail->text();

    Konekcija baza;
    baza.dbOpen();

    QSqlQuery upit;

    upit.prepare("UPDATE Profesor SET Ime = :ime, Prezime = :prezime, DatumRodjenja = :datumRodjenja, Telefon = :telefon, E_mail = :mail WHERE ProfesorID = :profesorID;");
    upit.bindValue(":ime", ime);
    upit.bindValue(":prezime", prezime);
    upit.bindValue(":datumRodjenja", datumRodjenja);
    upit.bindValue(":telefon", telefon);
    upit.bindValue(":mail", mail);
    upit.bindValue(":profesorID", profesorID);

    upit.exec();

    QMessageBox::information(this, "Uspesno!!!", "Podaci o profesoru su uspesno izmenjeni!!!");

    baza.dbClose();

    ui->lineEditSifra->clear();
    ui->lineEditIme->clear();
    ui->lineEditPrezime->clear();
    ui->lineEditTelefon->clear();
    ui->lineEditMail->clear();
    ui->dateEditDatumRodjenja->setDate(QDate::currentDate());
}

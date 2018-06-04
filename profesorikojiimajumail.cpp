#include "profesorikojiimajumail.h"
#include "ui_profesorikojiimajumail.h"
#include "konekcija.h"
#include <QMessageBox>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>

QT_CHARTS_USE_NAMESPACE

ProfesoriKojiImajuMail::ProfesoriKojiImajuMail(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProfesoriKojiImajuMail)
{
    ui->setupUi(this);
}

ProfesoriKojiImajuMail::~ProfesoriKojiImajuMail()
{
    delete ui;
}

void ProfesoriKojiImajuMail::on_pushButtonIzadji_clicked()
{
    this->close();
}

void ProfesoriKojiImajuMail::on_pushButtonPrikazi_clicked()
{
    Konekcija baza;
    baza.dbOpen();

    int rbMesec = ui->spinBoxMesec->text().toInt();
    QString imeMesec[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    QString godina = ui->spinBoxGodina->text();

    QSqlQuery upit;

    upit.prepare("SELECT Profesor.Ime, Profesor.Prezime, COUNT (Kontakt_Informacije.DatumKontakta) AS [Broj kontakta] FROM Profesor INNER JOIN Kontakt_Informacije ON Profesor.ProfesorID = Kontakt_Informacije.ProfesorID WHERE (Profesor.E_mail NOT NULL) AND (Kontakt_Informacije.DatumKontakta LIKE '%" + imeMesec[rbMesec - 1] + "%') AND (Kontakt_Informacije.DatumKontakta LIKE '%" + godina + "') GROUP BY Profesor.ProfesorID ORDER BY [Broj kontakta] DESC;");

    upit.exec();

    QSqlQueryModel *model;
    model = new QSqlQueryModel();
    model->setQuery(upit);
    ui->tableView->setModel(model);

    baza.dbClose();
}

void ProfesoriKojiImajuMail::on_pushButtonNacrtaj_clicked()
{
    QPieSeries *serija = new QPieSeries();

    Konekcija baza;
    baza.dbOpen();

    int rbMesec = ui->spinBoxMesec->text().toInt();
    QString imeMesec[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    QString godina = ui->spinBoxGodina->text();

    QSqlQuery upit;

    upit.prepare("SELECT Profesor.Prezime, COUNT (Kontakt_Informacije.DatumKontakta) AS [Broj kontakta] FROM Profesor INNER JOIN Kontakt_Informacije ON Profesor.ProfesorID = Kontakt_Informacije.ProfesorID WHERE (Profesor.E_mail NOT NULL) AND (Kontakt_Informacije.DatumKontakta LIKE '%" + imeMesec[rbMesec - 1] + "%') AND (Kontakt_Informacije.DatumKontakta LIKE '%" + godina + "') GROUP BY Profesor.ProfesorID ORDER BY [Broj kontakta] DESC;");

    upit.exec();

    while(upit.next())
    {
        serija->append(upit.value(0).toString(), upit.value(1).toInt());
    }

    baza.dbClose();

    QChart *grafikon = new QChart();
    grafikon->addSeries(serija);

    grafikon->legend()->setVisible(true);
    grafikon->legend()->setAlignment(Qt::AlignRight);

    QChartView *chartView = new QChartView(grafikon);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->gridLayout->addWidget(chartView, 0, 0);
}

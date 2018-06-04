#ifndef PROFESORIKOJIIMAJUMAIL_H
#define PROFESORIKOJIIMAJUMAIL_H

#include <QDialog>

namespace Ui {
class ProfesoriKojiImajuMail;
}

class ProfesoriKojiImajuMail : public QDialog
{
    Q_OBJECT

public:
    explicit ProfesoriKojiImajuMail(QWidget *parent = 0);
    ~ProfesoriKojiImajuMail();

private slots:
    void on_pushButtonIzadji_clicked();

    void on_pushButtonPrikazi_clicked();

    void on_pushButtonNacrtaj_clicked();

private:
    Ui::ProfesoriKojiImajuMail *ui;
};

#endif // PROFESORIKOJIIMAJUMAIL_H

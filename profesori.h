#ifndef PROFESORI_H
#define PROFESORI_H

#include <QDialog>

namespace Ui {
class Profesori;
}

class Profesori : public QDialog
{
    Q_OBJECT

public:
    explicit Profesori(QWidget *parent = 0);
    ~Profesori();

private slots:
    void on_pushButtonIzadji_clicked();

    void on_pushButtonNovi_clicked();

    void on_pushButtonUpisi_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_pushButtonIzmeni_clicked();

private:
    Ui::Profesori *ui;
};

#endif // PROFESORI_H

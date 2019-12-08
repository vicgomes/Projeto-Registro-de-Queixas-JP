#ifndef DIALOGEDITARQUEIXA_H
#define DIALOGEDITARQUEIXA_H

#include <QDialog>
#include <QMessageBox>
#include <mainwindow.h>

#include "queixa.h"
#include "tempo.h"

namespace Ui {
class DialogEditarQueixa;
}

class DialogEditarQueixa : public QDialog
{
    Q_OBJECT

public:
    explicit DialogEditarQueixa(QWidget *parent = nullptr);
    ~DialogEditarQueixa();

    bool getExcluir() const;
    void setExcluir(bool value);

    Queixa getNova();
    void setNova();
    void setNova(Queixa x);

    bool nova;

    // funções reutilizadas
    QString ajustando_data(QString &dia, QString &mes, QString &ano);
    bool testar_campo(QString s);

private slots:

    void on_btnCancelar_clicked();

    void on_btnApagar_clicked();

    void on_btnSalvar_clicked();

private:
    Ui::DialogEditarQueixa *ui;

    Queixa editada;

    bool excluir;

};

#endif // DIALOGEDITARQUEIXA_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QVector>
#include <QMap>

#include "queixa.h"
#include "sistema.h"
#include "tempo.h"
#include "dialogeditarqueixa.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void input_tabelas(Queixa x, int linha);
    void atualizar_tabela();

    QString ajustando_data(QString &dia, QString &mes, QString &ano);

    bool testar_campo(QString s);

    void esvaziar();

    void estatisticas();

private slots:
    void on_pushButtonCadastrar_clicked();

    void on_btnOrdenarPorBairro_clicked();

    void on_btnAntigas_clicked();

    void on_btnRecentes_clicked();

    void on_actionSalvar_triggered();

    void on_actionCarregar_triggered();

    void on_tabelaGeral_cellDoubleClicked(int row, int column);

private:
    Ui::MainWindow *ui;
    Sistema sistema;

    QMap<QString, int> contadorBairro;         // servirá pra contar o número de incidentes por bairro
    QVector<Queixa> backup;                    // para salvar o estado inicial da tabela
    int num;                                   // para contar a quantidade de queixas registradas no total

};

#endif // MAINWINDOW_H

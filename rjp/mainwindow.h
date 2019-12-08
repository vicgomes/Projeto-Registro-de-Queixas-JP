#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QVector>
#include <algorithm>

#include "queixa.h"
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

    void estatisticas(int linha);

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

    QVector<Queixa> sistema;
    QVector<Queixa> backup;                    // para salvar o estado inicial da tabela

};

#endif // MAINWINDOW_H

#include "mainwindow.h"
#include "ui_mainwindow.h"

#define MIN_LETRAS 3
#define INDICE_MAX 2
#define DATA_MIN 2

const QString VAZIO = "  ---"; //texto no primeiro slot da ComboBox


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tabelaGeral->verticalHeader()->setVisible(false); // para remover a coluna informando o número de cada linha

    ui->tabelaEstatisticaBairro->setColumnWidth(0, 220);

    // para não ser possível editar diretamente na tabela
    ui->tabelaGeral->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tabelaEstatisticaBairro->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonCadastrar_clicked() // o botão de submeter queixa
{
    // declarando e atribuindo valores às variáveis
    Queixa queixa;

    QString nome_temp = ui->inputNome->text();
    QString boxBairro = ui->BoxBairro->currentText();

    QDate data = ui->inputDataOcorrido->date();
    QString dd = QString::number(ui->inputDataOcorrido->date().day());
    QString mm = QString::number(ui->inputDataOcorrido->date().month());
    QString aa = QString::number(ui->inputDataOcorrido->date().year());

    QString prob_temp = ui->boxProblema->currentText();
    QString desc_temp = ui->inputProblema->text();

    bool campo_nome = testar_campo(nome_temp);
    bool campo_bairro = testar_campo(boxBairro);
    bool campo_problema = testar_campo(prob_temp);


    /* testando se os campos estão devidamente preenchidos
    e inserindo alguns valores na classe */
    if((campo_nome and campo_bairro and campo_problema) == true)
    {
        queixa.setNome(nome_temp);                                  // nome
        queixa.setBairro(boxBairro);                                // bairro
        queixa.setdataOcorrido(ajustando_data(dd, mm, aa));         // data do ocorrido
        queixa.setData(data);
        queixa.setProblema(prob_temp);                              // problema
        queixa.setProbComDescricao(prob_temp, desc_temp);           // descrição de cada problema

        // adicionando ao vetor da classe Sistema
        sistema.inserir_queixa(queixa);
        backup = sistema.getSistema();
        contadorBairro[queixa.getBairro()]++;
        num++;

        // inserindo as queixas na tabela geral
        int linha = ui->tabelaGeral->rowCount();
        ui->tabelaGeral->insertRow(linha);
        input_tabelas(queixa, linha);
        estatisticas();
    }


    esvaziar();
}

void MainWindow::input_tabelas(Queixa x, int linha)
{
    ui->tabelaGeral->setItem(linha,0, new QTableWidgetItem(x.getBairro()));
    ui->tabelaGeral->setItem(linha,1, new QTableWidgetItem(getData()));
    ui->tabelaGeral->setItem(linha,2, new QTableWidgetItem(x.getdataOcorrido()));
    ui->tabelaGeral->setItem(linha,3, new QTableWidgetItem(x.getProblema()));
}

void MainWindow::atualizar_tabela()
{
    ui->tabelaGeral->setRowCount(0);

    for(auto mostrar : sistema.sistema)
    {
        int linha = ui->tabelaGeral->rowCount();
        ui->tabelaGeral->insertRow(linha);
        ui->tabelaGeral->setRowHeight(linha, 40);

        ui->tabelaGeral->setItem(linha,0, new QTableWidgetItem(mostrar.getBairro()));
        ui->tabelaGeral->setItem(linha,1, new QTableWidgetItem(getData()));
        ui->tabelaGeral->setItem(linha,2, new QTableWidgetItem(mostrar.getdataOcorrido()));
        ui->tabelaGeral->setItem(linha,3, new QTableWidgetItem(mostrar.getProblema()));
    }


}

QString MainWindow::ajustando_data(QString &dia, QString &mes, QString &ano)
{
    QString data_temp;
    if(dia.length() < DATA_MIN)
    {
        dia = "0"+dia;
    }
    if(mes.length() < DATA_MIN)
    {
        mes = "0"+mes;
    }
    data_temp = dia+"/"+mes+"/"+ano;

    return data_temp;
}

bool MainWindow::testar_campo(QString s)
{
    int contador = 0;
    for(int i = 0; i < s.length(); i++)
    {
        if(s[i] == " ")
            contador++;
    }
    if(s.length() == contador)
    {
        QMessageBox::warning(this, "Erro", "Espaço(s) deixado(s) em branco. Por favor, preencha.");
        return false;
    }

    if(s == "\0")
    {
        return false;
    }

    if(s == VAZIO)
    {
        QMessageBox::warning(this, "ERRO", "Você não selecionou nenhum bairro e/ou nenhum problema!");
        return false;
    }

    if(s.length() < MIN_LETRAS)
    {
        QMessageBox::warning(this, "ERRO", "Inválido. O número de caracteres inserido é muito pequeno.");
        return false;
    }

    else return true;
}

void MainWindow::esvaziar()
{
    ui->inputNome->clear();
    ui->BoxBairro->setCurrentIndex(0);
    ui->boxProblema->setCurrentIndex(0);
    ui->inputProblema->clear();
}

void MainWindow::estatisticas()
{
    QVector<QString> retorno;
    QString temp;
    int queixas = 0;

    for(auto x : contadorBairro.keys())
    {
        if(contadorBairro.value(x) > queixas)
        {
            temp = x;
            queixas = contadorBairro.value(x);
        }
    }

    ui->tabelaEstatisticaBairro->setItem(0,0, new QTableWidgetItem(temp));
    ui->tabelaEstatisticaBairro->setItem(0,1, new QTableWidgetItem(QString::number(queixas)));

    ui->numQueixas->setText(QString::number(num));
}

void MainWindow::on_btnOrdenarPorBairro_clicked()
{
    ui->tabelaGeral->clearContents();        // limpando para reorganizar
    sistema.organizarPorBairro();

    for(int i = 0;i < sistema.size();i++)
    {
        input_tabelas(sistema[i], i);
    }
}

void MainWindow::on_btnAntigas_clicked()
{
   ui->tabelaGeral->clearContents();

   for(int i = 0;i < backup.size();i++)
   {
       input_tabelas(backup[i], i);
   }
}

void MainWindow::on_btnRecentes_clicked()
{
    ui->tabelaGeral->clearContents();
    QVector<Queixa> inverso;

    for(int j = sistema.size()-1;j >= 0;j--)
    {
        inverso.push_back(backup[j]);
    }

    for(int k = 0;k < inverso.size();k++)
    {
        input_tabelas(inverso[k], k);
    }
}

void MainWindow::on_actionSalvar_triggered()
{
    QString filename;
    filename = QFileDialog::getSaveFileName(this,"Salvar arquivo","","*.csv");
    if(sistema.salvar(filename) == true)
    {
        QMessageBox::information(this,"Salvo","Arquivo salvo com sucesso!");
    }

    else QMessageBox::critical(this,"Erro", "O arquivo não foi salvo.");
}

void MainWindow::on_actionCarregar_triggered()
{
    QString filename;
    filename = QFileDialog::getOpenFileName(this, "Abrir arquivo","","Arquivo separado por vírgulas(*.csv)");
    if(sistema.carregar(filename) == true)
    {
        QMessageBox::critical(this,"Arquivo","O arquivo já foi lido, favor cheque a tabela!");
    }
    else
    {
        for(int i = 0;i < sistema.size();i++)
        {
            ui->tabelaGeral->insertRow(i);
            input_tabelas(sistema[i], i);
        }

        QMessageBox::information(this,"Arquivo"," O arquivo foi lido, cheque a tabela!");
        estatisticas();
    }
}

void MainWindow::on_tabelaGeral_cellDoubleClicked(int row, int column)
{
    DialogEditarQueixa edit;
    edit.setNova(sistema[row]);

    column = 0;
    if(edit.getExcluir())
    {
        sistema.sistema.erase(sistema.sistema.begin()+row);
        atualizar_tabela();
    }

    if(edit.nova)
    {
        sistema[row] = edit.getNova();
        atualizar_tabela();
    }
}






















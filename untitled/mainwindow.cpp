#include "mainwindow.h"
#include "ui_mainwindow.h"

#define MIN_LETRAS 3
#define INDICE_MAX 2
#define DATA_MIN 2


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

    QString boxBairro = ui->BoxBairro->currentText();

    QDate data = ui->inputDataOcorrido->date();
    QString dd = QString::number(ui->inputDataOcorrido->date().day());
    QString mm = QString::number(ui->inputDataOcorrido->date().month());
    QString aa = QString::number(ui->inputDataOcorrido->date().year());

    QString prob_temp = ui->boxProblema->currentText();

    bool campo_bairro = testar_campo(boxBairro);
    bool campo_problema = testar_campo(prob_temp);


    /* testando se os campos estão devidamente preenchidos
    e inserindo alguns valores na classe */
    if(campo_bairro and campo_problema)
    {
        qDebug() << "cu";
        queixa.setBairro(boxBairro);                                // bairro
        queixa.setdataOcorrido(ajustando_data(dd, mm, aa));         // data do ocorrido
        queixa.setData(data);
        queixa.setProblema(prob_temp);                              // problema
        qDebug() << "cu";
        // adicionando ao vetor da classe Sistema
        sistema.push_back(queixa);
        qDebug() << "cu";
        backup = sistema;
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

    for(auto mostrar : sistema)
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
    ui->BoxBairro->setCurrentIndex(0);
    ui->boxProblema->setCurrentIndex(0);
}

void MainWindow::estatisticas()
{
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
    ui->tabelaGeral->clearContents();                                 // limpando para reorganizar

    std::sort(sistema.begin(), sistema.end(), [](Queixa a, Queixa b)  // função implícita
    {
        return a.getBairro() < b.getBairro();
    });


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
    QFile arquivo(filename);

        arquivo.open(QIODevice::WriteOnly);
        if(arquivo.isOpen() == true)
        {
            for(auto e : sistema)
            {
                QString line = e.getBairro()+";"+e.getdataOcorrido()+";"+e.getProblema()+"\0";
                arquivo.write(line.toLocal8Bit());
            }

            arquivo.close();
            QMessageBox::information(this,"Salvo","Arquivo salvo com sucesso!");
        }
        else QMessageBox::critical(this,"Erro", "O arquivo não foi salvo.");
}

void MainWindow::on_actionCarregar_triggered()
{
    QString filename;
    filename = QFileDialog::getOpenFileName(this, "Abrir arquivo","","Arquivo separado por ;(*.csv)");
    QFile arquivo(filename);

    arquivo.open(QIODevice::ReadOnly);
    QString line;
    QStringList dados;
    while(!arquivo.atEnd())
    {
        Queixa y;
        QDate temp;
        line = arquivo.readLine();
        dados = line.split(";");

        y.setBairro(dados[0]);
        y.setData(temp.fromString(getData()));
        y.setdataOcorrido(dados[2]);
        y.setProblema(dados[3]);

        sistema.push_back(y);
    }
    arquivo.close();

    ui->tabelaGeral->setRowCount(0);     // para limpar a tabela
}

void MainWindow::on_tabelaGeral_cellDoubleClicked(int row, int column)
{
    DialogEditarQueixa edit;
    edit.setNova(sistema[row]);

    column = 0;
    if(edit.getExcluir())
    {
        sistema.erase(sistema.begin()+row);
        atualizar_tabela();
    }

    if(edit.nova)
    {
        sistema[row] = edit.getNova();
        atualizar_tabela();
    }
}






















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
        queixa.setBairro(boxBairro);
        queixa.setdataOcorrido(ajustando_data(dd, mm, aa));
        queixa.setData(data);
        queixa.setProblema(prob_temp);

        // adicionando ao vetor da classe Sistema
        sistema.push_back(queixa);
        backup = sistema;

        // inserindo as queixas na tabela geral
        int l1 = ui->tabelaGeral->rowCount();
        ui->tabelaGeral->insertRow(l1);
        input_tabelas(queixa, l1);

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
    ui->tabelaGeral->setRowCount(0);                // zerar tabela

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
    if(s == VAZIO)
    {
        QMessageBox::warning(this, "ERRO", "Você não selecionou nenhum bairro e/ou nenhum problema!");
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
    QMap<QString, int> temp;
    QPair<QString, int> top1, top2, top3;

    for(auto problema : sistema)
        ++temp[problema.getBairro()];

    for(auto input : temp.toStdMap())
    {
        if(input.second > top3.second)
        {
            top3.first = input.first;
            top3.second = input.second;
        }
        if(top3.second > top2.second)
        {
            top2.first = input.first;
            top2.second = input.second;
        }
        if(top2.second > top1.second)
        {
            top1.first = input.first;
            top1.second = input.second;
        }
    }

    int linha = 3;
    ui->tabelaEstatisticaBairro->setItem(linha,0, new QTableWidgetItem(top1.first));
    ui->tabelaEstatisticaBairro->setItem(linha,1, new QTableWidgetItem(QString::number(top1.second)));
    ui->tabelaEstatisticaBairro->setItem(linha,0, new QTableWidgetItem(top2.first));
    ui->tabelaEstatisticaBairro->setItem(linha,1, new QTableWidgetItem(QString::number(top2.second)));
    ui->tabelaEstatisticaBairro->setItem(linha,0, new QTableWidgetItem(top3.first));
    ui->tabelaEstatisticaBairro->setItem(linha,1, new QTableWidgetItem(QString::number(top3.second)));

    ui->numQueixas->setText(QString::number(sistema.size()));
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
    edit.setWindowTitle("Editar queixa");
    edit.setModal(true);
    edit.exec();

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






















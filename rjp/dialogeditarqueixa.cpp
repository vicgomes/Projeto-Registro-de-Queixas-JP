#include "dialogeditarqueixa.h"
#include "ui_dialogeditarqueixa.h"

#define MIN_LETRAS 3
#define DATA_MIN 2

const QString VAZIO = "  ---";

DialogEditarQueixa::DialogEditarQueixa(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogEditarQueixa)
{
    ui->setupUi(this);

    nova = false;
    excluir = false;
}

DialogEditarQueixa::~DialogEditarQueixa()
{
    delete ui;
}

void DialogEditarQueixa::on_btnCancelar_clicked()
{
    close();
}

void DialogEditarQueixa::on_btnApagar_clicked()
{
    setExcluir(false);
    close();
}

void DialogEditarQueixa::on_btnSalvar_clicked()
{
    setNova();
    nova = true;

    close();
}

bool DialogEditarQueixa::getExcluir() const
{
    return excluir;
}

void DialogEditarQueixa::setExcluir(bool value)
{
    excluir = value;
}

Queixa DialogEditarQueixa::getNova()
{
    return editada;
}

void DialogEditarQueixa::setNova()
{
    QString boxBairro = ui->EditBoxBairro->currentText();

    QDate data = ui->dataNova->date();
    QString dd = QString::number(ui->dataNova->date().day());
    QString mm = QString::number(ui->dataNova->date().month());
    QString aa = QString::number(ui->dataNova->date().year());

    QString prob_temp = ui->EditBoxProblema->currentText();

    bool campo_problema = testar_campo(prob_temp);
    bool campo_bairro = testar_campo(boxBairro);


    if((campo_problema and campo_bairro) == true)
    {
        editada.setBairro(boxBairro);
        editada.setdataOcorrido(ajustando_data(dd, mm, aa));
        editada.setData(data);
        editada.setProblema(prob_temp);
    }
}

void DialogEditarQueixa::setNova(Queixa x)
{
    editada = x;

    ui->EditBoxBairro->setCurrentText(x.getBairro());
    ui->dataNova->setDate(x.getData());
    ui->EditBoxProblema->setCurrentText(x.getProblema());
}

QString DialogEditarQueixa::ajustando_data(QString &dia, QString &mes, QString &ano)
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

bool DialogEditarQueixa::testar_campo(QString s)
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



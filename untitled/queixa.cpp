#include "queixa.h"

QMap<QString, QString> Queixa::getProbComDescricao() const
{
    return probComDescricao;
}

void Queixa::setProbComDescricao(const QString p, const QString d)
{
    probComDescricao[p] = d;
}

QDate Queixa::getData() const
{
    return data;
}

void Queixa::setData(const QDate &value)
{
    data = value;
}

Queixa::Queixa()
{
    
}

QString Queixa::getNome() const
{
    return nome;
}

void Queixa::setNome(const QString &value)
{
    nome = value;
}

QString Queixa::getBairro() const
{
    return bairro;
}

void Queixa::setBairro(const QString &value)
{
    bairro = value;
}

QString Queixa::getProblema() const
{
    return problema;
}

void Queixa::setProblema(const QString &value)
{
    problema = value;
}

QString Queixa::getdataOcorrido() const
{
    return dataOcorrido;
}

void Queixa::setdataOcorrido(QString value)
{
    dataOcorrido = value;
}

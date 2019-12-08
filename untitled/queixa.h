#ifndef QUEIXA_H
#define QUEIXA_H

#include <QString>
#include <QVector>
#include <QDate>
#include <QMap>

class Queixa
{
private:
    QString bairro;

    QString dataOcorrido;
    QDate data;

    QString problema;
    QMap<QString, QString> probComDescricao;   // guardará as descrições dos problemas

public:
    Queixa();

    QString getBairro() const;
    void setBairro(const QString &value);

    QString getProblema() const;
    void setProblema(const QString &value);

    QString getdataOcorrido() const;
    void setdataOcorrido(QString value);

    QMap<QString, QString> getProbComDescricao() const;
    void setProbComDescricao(const QString p, const QString d);

    QDate getData() const;
    void setData(const QDate &value);
};

#endif // QUEIXA_H

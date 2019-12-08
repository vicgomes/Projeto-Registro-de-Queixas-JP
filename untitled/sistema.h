#ifndef SISTEMA_H
#define SISTEMA_H

#include <QFileDialog>
#include <QVector>
#include <QString>
#include <algorithm>

#include "queixa.h"

class Sistema : public Queixa
{
public:
    Sistema();
    Queixa operator[](int a);
    QVector<Queixa> sistema;

    QVector<Queixa> getSistema();
    int size();

    void inserir_queixa(Queixa q);

    void organizarPorBairro();
    void organizarPorDataOcorrido();

    bool salvar(QString dados);
    bool carregar(QString d);
};

#endif // SISTEMA_H

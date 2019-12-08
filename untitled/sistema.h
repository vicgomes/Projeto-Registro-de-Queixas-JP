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

    void organizarPorBairro(QVector<Queixa> &sistema);
    void organizarPorDataOcorrido();

    bool salvar(QString dados);
    bool carregar(QString d);
};

#endif // SISTEMA_H

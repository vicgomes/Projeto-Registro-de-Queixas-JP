#include "sistema.h"

#define NUM_QUEIXA_MIN 1

Sistema::Sistema()
{

}

//bool Sistema::salvar(QString dados)
//{
//    QFile arquivo(dados);

//        arquivo.open(QIODevice::WriteOnly);
//        if(arquivo.isOpen() == true)
//        {
//            for(auto e : sistema)
//            {
//                QString line = e.getBairro()+";"+e.getdataOcorrido()+";"+e.getProblema()+"\0";
//                arquivo.write(line.toLocal8Bit());
//            }

//            arquivo.close();
//            return true;
//        }

//        else return false;
//}

//bool Sistema::carregar(QString d)
//{
//    QFile arquivo(d);

//        if(arquivo.isOpen() == 1)return 1;
//        else
//        {
//            arquivo.open(QIODevice::ReadOnly);
//            QString line;
//            QStringList dados;
//            while(!arquivo.atEnd())
//            {
//                Queixa y;
//                line = arquivo.readLine();
//                dados = line.split(";");

//                y.setBairro(dados[0]);
//                y.setData(getData());
//                y.setdataOcorrido(dados[2]);
//                y.setProblema(dados[3]);

//                //inserir_queixa(y);
//            }

//            return false;
//        }
//}

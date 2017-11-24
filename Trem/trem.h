#ifndef TREM_H
#define TREM_H

#include "vagao.h"
using namespace std;

class Trem{
    int maxVagoes;
    vector<Vagao> vagoes;
public:
    Trem(int maxVagoes = 0){
        this->maxVagoes = maxVagoes;
    }

    void addVagao(Vagao vagao){
        if((int)vagoes.size() >= maxVagoes)
            throw string("limite de vagoes atingido");
        vagoes.push_back(vagao);
    }

    bool embarcar(Passageiro* pass){
        for(Vagao& v : vagoes){
            if(v.getLotacao() < v.getCapacidade())
                if(v.embarcar(pass))
                    return true;
        }
        throw string("poltronas indisponiveis");
    }

    Passageiro* desembarcar(string cpf){
        Passageiro* aux;
        for(Vagao& v: vagoes){
            aux = v.desembarcar(cpf);
            if(aux)
                return aux;
        }
        throw string( cpf + "passageiro não está no trem" );
    }

    bool search(Passageiro* passageiro){
        for(Vagao v : vagoes){
            if(v.search(passageiro))
                return true;
        }
        return false;
    }

    int getLotacao(){
        int cont = 0;
        for(Vagao v : vagoes)
            cont = cont + v.getLotacao();
        return cont;
    }
    int getCapacidade(){
        int cont = 0;
        for(Vagao v : vagoes)
            cont = cont + v.getCapacidade();
        return cont;
    }
    string toString(){
        stringstream ss;
        ss << "Numero máximo de vagões: " << maxVagoes << endl;
        for(Vagao v : vagoes)
            ss << v.toString() << endl;
        return ss.str();
    }
};
#endif // TREM_H

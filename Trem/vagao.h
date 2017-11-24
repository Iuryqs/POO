#ifndef VAGAO_H
#define VAGAO_H

#include <vector>
#include <algorithm>
#include "passageiros.h"

using namespace std;

class Vagao{
    int capacidade;
    int id;
    vector<Passageiro*> cadeiras;
public:
    Vagao(int id = 0, int capacidade = 0):
        cadeiras(capacidade, nullptr){
        this->id = id;
        this->capacidade = capacidade;
    }

    bool embarcar(Passageiro * passageiro){
        for(int i = 0; i < (int) cadeiras.size(); i++){
            if(!cadeiras[i]){
                cadeiras[i] = passageiro;
                return true;
            }
        }
        return false;
    }

    Passageiro* desembarcar(string cpf){
        Passageiro* aux;
        for(int i = 0; i < (int) cadeiras.size(); i++){
            if(cadeiras[i]->getCpf() == cpf){
                aux = cadeiras[i];
                cadeiras[i] = nullptr;
                return aux;
            }
        }
        return nullptr;
    }

    bool search(Passageiro* passageiro){
        for(auto c : cadeiras){
            if((c != nullptr) && (c->getCpf() == passageiro->getCpf())){
                return true;
            }
        }
        return false;
    }

    string toString(){
        stringstream ss;
        ss << "Vagão: " << this->id << endl;
        ss << "Capacidade: " << this->capacidade << endl;
        ss << "[";
        for(int i = 0; i < (int) cadeiras.size(); i++){
            if(!cadeiras[i])
                ss << "_";
            else
                ss << "CPF: " << cadeiras[i]->getCpf() << " ";
        }
        ss << "]";
        return ss.str();
    }

    int getCapacidade(){
        return this-> capacidade;
    }

    int getLotacao(){
        int cont = 0;
        for(Passageiro * pass : cadeiras){
            if(pass)
                cont++;
        }
        return cont;
    }

};

#endif // VAGAO_H

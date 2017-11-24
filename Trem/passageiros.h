#ifndef PASSAGEIROS_H
#define PASSAGEIROS_H

#include <iostream>
#include <sstream>

using namespace std;

class Passageiro{
    string cpf;
public:
    Passageiro(string cpf){
        this->cpf = cpf;
    }
    string getCpf(){
        return this->cpf;
    }
    string toString(){
        stringstream ss;
        ss <<  "CPF: " << this->cpf << endl;
        return ss.str();
    }
};

#endif // PASSAGEIROS_H

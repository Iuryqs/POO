#ifndef REGISTROPASSAGEIROS_H
#define REGISTROPASSAGEIROS_H

#include <vector>
#include <algorithm>
#include "passageiros.h"

using namespace std;

bool comparaNome(Passageiro x, Passageiro y){
    return x.getCpf() < y.getCpf();
}

class RegistroPassageiro{
    vector<Passageiro> passageiros;
public:
    RegistroPassageiro(){
    }

    void addPass(Passageiro pass){
        passageiros.push_back(pass);
    }

    vector<Passageiro> getAllPass(){
        return passageiros;
    }

    string toString(){
        stringstream ss;
        sort(passageiros.begin(), passageiros.end(), comparaNome);
        ss << "Passageiros:" << endl;
        for(Passageiro p : passageiros)
            ss <<  "-" << p.toString() << endl;
        return ss.str();
    }
};

#endif // REGISTROPASSAGEIROS_H

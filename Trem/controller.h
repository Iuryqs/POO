#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <sstream>
#include <vector>

#include "trem.h"
#include "vagao.h"
#include "passageiros.h"
#include "registropassageiros.h"

using namespace std;

template <class T>
T cast(string palavra){
    T value;
    stringstream(palavra) >> value;
    return value;
}

//split da aula s09e01 a
vector<string> split(string line){
    vector<string> saida;
    stringstream ss(line);
    string palavra;
    while(ss >> palavra)
        saida.push_back(palavra);
    return saida;
}

inline int Int(std::string word){
    return cast<int>(word);
}

inline int Float(std::string word){
    return cast<float>(word);
}


class Controller{
    Trem trem;
    RegistroPassageiro registro;
    int id{0};
public:
    Controller(){
    }

    string process(string line){
        auto ui = split(line);
        auto cmd = ui[0];

        if(cmd == "help"){
            return  "iniciarTrem _qtdVagoes \n"
                    "addVagao _capacidade \n"
                    "embarcar _passCpf \n"
                    "desembarque _passCpf \n"
                    "show \n"
                    "registro \n"
                    "fim \n";
        }

        if(cmd == "iniciarTrem"){
            int qtdVagoes = Int(ui[1]);
            trem = Trem(qtdVagoes);
            string aux = "Trem iniciado com um total de vagão = " + ui[1] + ".\n";
            return aux;
        }

        if("addVagao" == cmd){
            int capacidade = Int(ui[1]);
            Vagao v = Vagao(id, capacidade);
            trem.addVagao(v);
            id++;
            return "Vagao adicionado.\n";
        }

        if(cmd == "embarcar"){
            Passageiro* aux = new Passageiro(ui[1]);
            if(trem.search(aux))
                throw string("CPF já embarcado.");
            trem.embarcar(aux);
            registro.addPass(*aux);
            return "Passageiro " + aux->getCpf() + " embarcado com sucesso.";
        }

        if(cmd == "desembarque"){
            Passageiro * pass = trem.desembarcar(ui[1]);
            delete pass;
            return "Passageiro " + ui[1] + " desembarcado";
        }

        if(cmd == "show"){
            return trem.toString();
        }

        if(cmd == "registro"){
            return registro.toString();
        }

        return "";
    }

//commandLine da aula s09e01 a
    void commandLine() {
        string line = "";
        while(line != "fim"){
            cout << "(help): ";
            getline(cin, line);
            if(line == "")
                continue;
            cout << ">> " << line << endl;
            try {
                cout << process(line) << endl;
            } catch(const string& erro) {
                cout << erro << endl;
            }
        }
    }
};






#endif // CONTROLLER_H

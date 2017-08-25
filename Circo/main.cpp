#include <iostream>
#include <vector>

using namespace std;

class Comida {
public:
    string nome;
    int valor;

    Comida (string nome = "Pipoca",int valor = 3){
        this->nome = nome;
        this->valor = valor;
    }

};

class Circense{
public:
    string nome;
    string especialidade;
    Circense(string nome = "Tanguinha", string especialidade = "palhaco"){
        this->nome = nome;
        this->especialidade = especialidade;
    }
};

class Pessoa{
public:
    string nome;
    vector<string> preferencias;
    int idade;
    int alegria{0};
    bool fome;
    vector<string> quer_comer;
    int dinheirinho{10};

    Pessoa(string nome = "", int idade = 18, vector<string> preferencias = vector<string>(), vector<string> quer_comer = vector<string>()){
        this->nome = nome;
        this->idade = idade;
        this->alegria = 0;
        this->preferencias = preferencias;
        this->quer_comer = quer_comer;
        this->fome = true;
        this->dinheirinho = 10;
    }

    void verEspetaculo(vector<Circense> vetor){

        for (Circense& circense : vetor)
            for(string pref : preferencias)
                if(circense.especialidade == pref )
                    this->alegria += 1;

        /* MODO INDEXADO
         * for (int i = 0; i < vetor.size(); i++)
            for(int j = 0; j < preferencias.size(); j++)
                if(vetor[i].especialidade == preferencias[j])
                    this->alegria += 1;
        */

    }

    void comprarComida (vector<Comida> vet){

        for (Comida& comida : vet){
            for (string quer : quer_comer)
                if (comida.nome == quer){
                    this->fome = false;
                    if(dinheirinho >= comida.valor){
                        dinheirinho -= comida.valor;
                    } else {
                        cout << "Dinheiro insuficiente." << endl;
                    }
                }
        }

    }


    void addPreferencias(string pref){
        preferencias.push_back(pref);
    }

    void addQuerComer(string comercomer){
        quer_comer.push_back(comercomer);
    }



};

#include <vector>
#include <sstream>
int main(){

    vector<Comida> paraVender = {Comida("Pipoca", 4),
                                 Comida("Bombom", 1),
                                 Comida("Macarrão", 5)};


    vector<Pessoa> plateia = {Pessoa("Bia", 5, {"palhaco", "domador", "magico"}, {"Pipoca", "Bombom"}),
                              Pessoa("Ruy", 50, {"contorcionista"}, {"Chocolate", "Chilito"})};


    vector<Circense> atracoes = {Circense("Tanguinha", "palhaco"),
                                 Circense("Shazam", "magico"),
                                 Circense("Juvenal", "domador"),
                                 Circense("Valentina", "contorcionista")};



    for(Pessoa &pessoa : plateia)
        pessoa.verEspetaculo(atracoes);

    for(Pessoa &pessoa : plateia)
        pessoa.comprarComida(paraVender);

    for(Pessoa &pessoa : plateia){
        cout << "Nome: " << pessoa.nome << "\n" << "Alegria: " << pessoa.alegria << "\n" << "Dinheiro restante: "
             << pessoa.dinheirinho << "\n" << "Situação de saciedade: " << pessoa.fome << endl;
    }

}

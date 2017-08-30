#include <vector>
#include <iostream>

using namespace std;

struct Espiral{
    string nome;
    int qtd;
    float value;
    Espiral(int qtd = 0, string nome = "", float value = 0.0f){
        this->nome = nome;
        this->qtd = qtd;
        this->value = value;

    }
};

class Maquina{
public:
    vector<Espiral> espirais;
    float saldoCliente{0.0f};
    float lucro;

    Maquina(int qtd = 0, float saldoCliente = 0.0f){
        this->saldoCliente = saldoCliente;
        for(int i = 0; i < qtd; i++)
            espirais.push_back(Espiral());
    }

    bool receberDinheiro(float value){
        if (value > 0){
            this->saldoCliente += value;
            return true;
        } else
            return false;
    }

    float getSaldo(){
        return this->saldoCliente;
    }

    float devolverTroco(){
        float troco;
        troco = this->saldoCliente;
        this->saldoCliente = 0;
        return troco;
    }

    bool alterarProduto(){

    }

    void vender(){

    }

    void mostrarStatus(){

    }


};



int main(){
    Maquina maquina;
    string op;
    cout << "digite help" << endl;
    while(op != "fim"){
        cin >> op;
        if(op == "help"){
            cout << endl
                 << "inserir _valor" << endl
                 << "saldo" << endl
                 << "troco" << endl
                 << "fim" << endl << endl;
        }

        if(op == "inserir"){
            float valor;
            cin >> valor;
            cout << (maquina.receberDinheiro(valor)? "Sucesso" : "Erro") << endl;
        }

        if(op == "saldo"){
            cout << maquina.getSaldo() << " Reais" << endl;
        }

        if(op == "troco"){
            cout << "Voce retirou " << maquina.devolverTroco() << " Reais" << endl;
        }
    }
}
























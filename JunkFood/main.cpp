#include <vector>
#include <iostream>
#include <sstream>

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
    float lucro{0};

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

    bool alterarProduto(int indice, string nome, int qtd, float valor){
        if((indice > (int)espirais.size()) || (nome == "") || (qtd <= 0) || (valor <= 0)){
            return false;
        }
        espirais[indice].nome = nome;
        espirais[indice].qtd = qtd;
        espirais[indice].value = valor;
            return true;
    }


    int vender(int indice){
        if(indice > (int)espirais.size()){
            return 1;
        }

        if(espirais[indice].qtd > 0){
            if(saldoCliente >= espirais[indice].value){
                espirais[indice].qtd -= 1;
                this->saldoCliente -= espirais[indice].value;
                this->lucro += espirais[indice].value;
                return 0;
            }else {
                return 2;
            }
        }else
            return 1;

    }

    string mostrarStatus(){
        stringstream ss;
        ss << "Saldo: " << this->saldoCliente << endl
           << "Lucro: " << this->lucro << endl;
        int i = 0;
        for(auto show : espirais){
            ss << "Indice: " << i << "/ Nome: " << show.nome << "/ Quantidade: " << show.qtd << "/ Valor: " << show.value << endl;
            i += 1;
        }

        return ss.str();
    }


};


void inicializar(Maquina& maquina){
    maquina.receberDinheiro(10);
    maquina.alterarProduto(0, "nescau", 5, 3);
    maquina.alterarProduto(1, "doritos", 6, 4);
    maquina.alterarProduto(2, "coca", 8, 3);
    maquina.alterarProduto(3, "agua", 9, 2);
}

int main(){
    Maquina maquina;
    string op;
    cout << "digite help ou alguma funcao" << endl;
    while(op != "fim"){
        cin >> op;
        if(op == "help"){
            cout << endl
                 << "inserir $valor" << endl
                 << "saldo" << endl
                 << "troco" << endl
                 << "iniciar $qtd" << endl
                 << "alterarEspiral $ind $nome $qtd $valor" << endl
                 << "comprar &ind" << endl
                 << "status" << endl
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

        if(op == "iniciar"){
            int valor;
            cin >> valor;
            maquina = Maquina(valor);
            inicializar(maquina);
            cout << "ok" << endl;
        }

        if(op == "alterarEspiral"){
            int indice;
            string nome;
            int qtd;
            float valor;
            cin >> indice; cin >> nome; cin >> qtd; cin >> valor;
            cout << (maquina.alterarProduto(indice, nome, qtd, valor)? "ok" : "erro") << endl;
        }

        if(op == "comprar"){
            int indice;
            cin >> indice;
            if(maquina.vender(indice) == 0){
                cout << "ok" << endl;
            }
            else if(maquina.vender(indice) == 1){
                cout << "erro(produto nao existe)" << endl;
            }
            else    if(maquina.vender(indice) == 2){
                cout << "erro(valor insuficiente)" << endl;
            }
        }

        if(op == "status"){
            cout << maquina.mostrarStatus();
        }
    }
}






















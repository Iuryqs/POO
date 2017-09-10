#include <iostream>
#include <vector>
#include <sstream>

using namespace std;


template <class T>
T read(){
    T t;
    cin >> t;
    return t;
}

struct Operacao{
    string descricao;
    float valor;
    Operacao(string descricao = "", float valor = 0){
        this->descricao = descricao;
        this->valor = valor;
    }
};

class Conta{
private:
    int id;
    float saldo{0};
    vector<Operacao> extrato;
public:
    Conta(int id = 0){
        this->id = id;
    }

    float getSaldo(){
        return this->saldo;
    }

    int getId(){
        return this->id;
    }

    void setId(int id){
        this->id = id;
    }

    bool saque(float valor){
        if((this->saldo < valor) || (valor < 0))
            return false;

        this->saldo -= valor;
        this->extrato.push_back(Operacao("Saque: -", valor));

        return true;
    }

    bool deposito(float valor){
        if(valor < 1)
            return false;

        this->saldo += valor;
        this->extrato.push_back(Operacao("Deposito: +", valor));
        return true;
    }

    vector<Operacao> getExtrato(){
        return this->extrato;
    }

    string extratoN(int valor){
        stringstream ss;
        int tamanho = (int)(extrato.size() - valor);
        for(; tamanho < (int)extrato.size(); tamanho++){
            ss << extrato[tamanho].descricao << " " << extrato[tamanho].valor << endl;
        }
        return ss.str();

    }

    bool transferir(Conta conta, float valor){

    }
};

class Cliente{
private:
    string cpf;
    vector<Conta> contas;
public:
    Conta(string cpf = ""){
        this->cpf = cpf;
    }

    int getCpf(){
        return this->cpf;
    }

    void setCpf(int id){
        this->cpf = cpf;
    }

    bool addConta(string numero){
    }

    bool encerrarConta(string numero){
    }
};

class Agencia{
private:
    vector<Cliente> clientes;
public:
    Agencia(){
    }

    bool addCliente(string cpf){
        for(auto cconta : contas){
            if(cliente.cpf == cpf){
                return false;
            }else{

            }
        }
    }

    bool abrirConta(string cpf){

    }
};

int main(){

    Conta conta;
    string op;
    cout << "digite help" << endl;
    while(op != "fim"){
        cin >> op;

        if(op == "help"){
            cout << "iniciar _id" << endl
                 << "saldo" << endl
                 << "saque _valor" << endl
                 << "deposito _valor" << endl
                 << "extrato" << endl
                 << "UltimoExtrato _valor" << endl
                 << "fim" << endl;
        }

        if(op == "iniciar"){
            conta = Conta(read<int>());
        }
        if(op == "saldo"){
            cout << conta.getSaldo() << endl;
        }
        if(op == "deposito"){
            cout << (conta.deposito(read<float>())? "ok" : "erro") << endl;
        }
        if(op == "saque"){
            cout << (conta.saque(read<float>())? "ok" : "erro") << endl;
        }
        if(op == "extrato"){
            for(auto operacao : conta.getExtrato()){
                cout << operacao.descricao << operacao.valor << endl;
            }
            cout << "Saldo Atual: " << conta.getSaldo();
        }
        if(op == "UltimoExtrato"){
            int valor;
            cin >> valor;
            cout << conta.extratoN(valor);
        }


    }

}

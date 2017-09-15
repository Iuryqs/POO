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
    bool ativa;
    float saldo{0};
    vector<Operacao> extrato;
public:
    Conta(int id = 0, bool ativa = true){
        this->id = id;
    }

    float getSaldo(){
        return this->saldo;
    }

    bool getAtiva(){
        return this->ativa;
    }

    void getAtiva(bool ativa){
        this->ativa = ativa;
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

//    bool transferir(Conta conta, float valor){

//    }
};

class Cliente{
private:
    string cpf;
    vector<Conta> contas;
public:
    Cliente(string cpf = ""){
        this->cpf = cpf;
    }
    string getCpf(){
        return this->cpf;
    }
    bool addConta(int numero){
        contas.push_back(numero);
        return true;
    }

    int encerrarConta(int numero){
        for(int i = 1; i < (int) contas.size(); i++){
            if(numero == contas[i].getId()){
                if(contas[i].getSaldo() > 0){
                    if(contas[i].getAtiva() == true){
                        contas[i].getAtiva(false);
                        return contas[i].getId();
                    }
                    return -3;
                }
                return -2;
            }
        }
        return -1;
    }
};

class Agencia{
public:
    int numeroConta = 0;
    vector<Cliente> clientes;
    Agencia(){
    }

    bool addCliente(string cpf){
        for(int i = 0; i < (int) clientes.size(); i++){

            if(clientes[i].getCpf() == cpf){
                return false;
            }
        }
        clientes.push_back(cpf);
        return true;
    }

    int abrirConta(string cpf){
        for(int i = 0; i < (int) clientes.size(); i++){
            if(clientes[i].getCpf() == cpf){
                clientes[i].addConta(numeroConta);
                numeroConta += 1;
                return numeroConta - 1;
            }
            return -1;
        }
    }
};

int main(){
    Conta conta;
    Agencia agencia;
    Cliente cliente;
    string op;
    cout << "digite help" << endl;
    while(op != "fim"){
        cin >> op;

        if(op == "help"){
            cout /*<< "iniciar _id" << endl
                 << "saldo" << endl
                 << "saque _valor" << endl
                 << "deposito _valor" << endl
                 << "extrato" << endl
                 << "UltimoExtrato _valor" << endl*/
                 << "addCli $cpf" << endl
                 << "abrirConta $cpf" << endl
                 << "encerrarConta $conta" << endl
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
            cout << "Saldo Atual: " << conta.getSaldo() << endl;
        }

        if(op == "UltimoExtrato"){
            int valor;
            cin >> valor;
            cout << conta.extratoN(valor);
        }

        if(op == "addCli"){
            cout << (agencia.addCliente(read<string>())? "Cliente adicionado" : "cpf duplicado") << endl;
        }

        if(op == "abrirConta"){
            int aux= agencia.abrirConta(read<string>());
            if(aux == -1){
                cout << "erro" << endl;
            }else{
                cout << "conta " << aux << " aberta" << endl;
            }

        }

        if(op == "encerrarConta"){
            int aux = cliente.encerrarConta(read<int>());
            if(aux < 0){
                if(aux == -1)
                    cout << "conta invalida" << endl;
                if(aux == -2)
                    cout << "saldo positivo" << endl;
                if(aux == -3)
                    cout << "conta ja esta encerrada" << endl;
            }else{
                cout << "conta " << aux << " encerrada" << endl;
            }
        }

    }

}

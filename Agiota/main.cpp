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

struct Transacao{
    int id;
    string nome;
    float valor;
    Transacao(int id = 0, string nome = "", float valor = 0){
        this->id = id;
        this->nome = nome;
        this->valor = valor;
    }
};

class Sistema{
  private:
    int nextId{0};
    vector<Transacao> transacoes;
    float balanco{0.0f};
  public:
    Sistema(float balanco = 0){
        this->balanco = balanco;
    }

    int addTran(string nome, float valor){
        if(valor < 0){
            if((valor * -1) > balanco){
                return -1;
            }
            this->transacoes.push_back(Transacao(nextId, nome, valor));
            this->balanco += valor;
            this->nextId += 1;
            return this->nextId;
        }else{
            this->transacoes.push_back(Transacao(nextId, nome, valor));
            this->balanco += valor;
            this->nextId += 1;
            return this->nextId;
        }
    }

    bool rmTran(int id){
        for(int i = 0; i < (int) transacoes.size(); i++){
            if(transacoes[i].id == id){
                balanco -= transacoes[i].valor;
                transacoes.erase(transacoes.begin() + i);
                return true;
            }
        }
        return false;

    }

    string showTran(){
        stringstream ss;
        ss << "Lista de transações:" << endl;
        for(Transacao i : transacoes){
            ss << "ID: " << i.id << " Nome: " << i.nome << " " << i.valor << "$" << endl;
        }
        return ss.str();

    }

    string showCliente(string nome){
        stringstream ss;
        float saldo = 0;
        ss << "Lista de transações de " << nome << endl;
        for(Transacao i : transacoes){
            if(i.nome == nome){
                ss << "ID: " << i.id << " Nome: " << i.nome << " " << i.valor << "$" << endl;
                saldo += i.valor;
            }
        }
        ss << "Saldo: " << saldo << endl;
        return ss.str();
    }

    int contarClientes(){
        vector<string> aux;
        int x = -1;
        bool y;

        for(Transacao i : transacoes){
            if(x == -1)
                aux.push_back(i.nome);

            y = true;

            for(x = 0; x < (int) aux.size(); x++){
                if(aux[x] == i.nome){
                    y = false;
                }
            }

            if(y == true)
                aux.push_back(i.nome);

        }
        return (int) aux.size();
    }

    float fazerBalanco(){
        return this->balanco;
    }

};

void inicializar(Sistema& sistema){
    sistema.addTran("Rafaella", 200);
    sistema.addTran("Iury", -100);
    sistema.addTran("Pedro", 400);
    sistema.addTran("Iury", 50);
    sistema.addTran("Toin", 50);
    sistema.addTran("Iury", -150);
}

int main(){
    Sistema sistema;
    string op;
    cout << "Digite o comando ou help: ";
    while(op != "fim"){
        cin >> op;
        if(op == "help"){
            cout << "iniciar $valor" << endl
                 << "addTran $nome $valor" << endl
                 << "rmTran $id" << endl
                 << "showTran" << endl
                 << "showCli $nome" << endl
                 << "contarCli" << endl
                 << "balanco" << endl << endl;
        }

        if(op == "iniciar"){
            float x = read<float>();
            sistema = Sistema(x);
            inicializar(sistema);
            cout << "Sistema iniciado com " << x << endl;
        }

        if(op == "addTran"){
            string nome = read<string>();
            float valor = read<float>();
            int x = sistema.addTran(nome, valor);
            if(x == -1){
                    cout << "Não há dinheiro suficiente para empréstimo" << endl;
            }else{
                    cout << "Transação " << x-1 << " adicionada"<< endl;
            }
        }

        if(op == "showTran"){
            cout << sistema.showTran();
        }

        if(op == "rmTran"){
            cout << (sistema.rmTran(read<int>())? "Transação removida" : "Transação não encontrada") << endl;
        }

        if(op == "showCli"){
            cout << sistema.showCliente(read<string>()) << endl;
        }

        if(op == "balanco"){
            cout << "Balanco: " << sistema.fazerBalanco() << endl;
        }

        if(op == "contarCli"){
            cout << "Existem " << sistema.contarClientes() << " clientes diferentes no Sistema." << endl;
        }
    }

    return 0;
}

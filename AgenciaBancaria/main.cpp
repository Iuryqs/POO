#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

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
    bool ativa{true};
    float saldo{0};
    vector<Operacao> extrato;
public:
    Conta(int id = 0){
        this->id = id;
    }

    float getSaldo(){
        return this->saldo;
    }

    bool getAtiva(){
        return this->ativa;
    }

    void setAtiva(bool ativa){
        this->ativa = ativa;
    }

    int getId(){
        return this->id;
    }

    void setId(int id){
        this->id = id;
    }

    bool sacar(float valor){
        if((this->saldo < valor) && (valor <= 0))
            return false;

        this->saldo -= valor;
        this->extrato.push_back(Operacao("saque: -", valor));

        return true;
    }

    bool depositar(float valor){
        if(valor < 1)
            return false;

        this->saldo += valor;
        this->extrato.push_back(Operacao("deposito: +", valor));
        return true;
    }

    string getExtrato(){
        stringstream ss;
        for(Operacao e: extrato){
            ss << e.descricao << e.valor << endl;
        }
        return ss.str();
    }

    string getExtratoN(int valor){
        stringstream ss;
        int tamanho = (int)(extrato.size() - valor);
        for(; tamanho < (int)extrato.size(); tamanho++){
            ss << extrato[tamanho].descricao << " " << extrato[tamanho].valor << endl;
        }
        return ss.str();

    }

    void transferir(int conta, float valor, string x){
        stringstream ss;
        ss << "transferência " << x << conta << " no valor de ";
        this->extrato.push_back(Operacao(ss.str(), valor));
    }
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
    vector<Conta>& getConta(){
        return this->contas;
    }

    int encerrarConta(int numero){
        for(int i = 0; i <= (int) contas.size(); i++){
            if(numero == contas[i].getId()){
                if(contas[i].getSaldo() > 0){
                    return -2;
                }

                if(contas[i].getAtiva() == false){
                    return -3;
                }

                contas[i].setAtiva(false);
                return contas[i].getId();
            }
        }
        return -1;
    }

    string saldo(int conta){
        stringstream ss;
        for(Conta c : contas){
                 if(c.getId() ==  conta){
                     if(c.getAtiva() == true){
                        ss << "saldo: " << c.getSaldo();
                        return ss.str();
                     }else
                        return "conta encerrada";
                }
        }
        ss << "conta inválida";
        return ss.str();
    }

    bool saque(int conta,float valor){
        for(Conta& c : contas){
            if(c.getId() == conta){
                if(c.getAtiva() == true)
                    return c.sacar(valor);
                else
                    return false;
            }
        }
    }

    bool deposito(int conta, float valor){
        for(Conta& c : contas){
            if(c.getId() == conta){
                if(c.getAtiva() == true)
                    return c.depositar(valor);
                else
                    return false;
            }
        }
    }

    string extrato(int conta){
        stringstream ss;
        for(Conta c : contas){
            if(conta == c.getId()){
                if(c.getAtiva() == true){
                    ss << "extrato:" << endl << c.getExtrato() << endl;
                    return ss.str();
                }else
                    return "conta encerrada";
            }
        }

    }

    string extratoN(int conta, int n){
        stringstream ss;
        for(Conta c : contas){
            if(conta == c.getId()){
                if(c.getAtiva() == true){
                    ss << "extratoN:" << endl << c.getExtratoN(n) << endl;
                    return ss.str();
                }else
                    return "conta encerrada";
            }
        }
    }

};

bool comparaNome(Cliente x, Cliente y){
    return x.getCpf() < y.getCpf();
}

class Agencia{
private:
    vector<Cliente> clientes;
public:
    int numeroConta = 0;
    vector<Conta> contas;

    Agencia(){
    }

    Cliente * Login(string cpf){
        for(Cliente& c : clientes){
            if(c.getCpf() == cpf){
                return &c;
            }
        }
        return nullptr;
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
        }
        return -1;
    }

    string showAllCli(){
        stringstream ss;
        int enumerador = 1;
        std::sort(clientes.begin(), clientes.end(), comparaNome);
        for(Cliente c : clientes){
            contas = c.getConta();
            vector<int> contasAtivas;
            for(Conta c1 : contas){
                if(c1.getAtiva())
                    contasAtivas.push_back(c1.getId());
            }
            ss << enumerador << " cpf: " << c.getCpf() << " contas: ";
            for(Conta c2 : contasAtivas)
                ss << c2.getId() << " ";
            ss << endl;
            enumerador += 1;
        }
        return ss.str();
    }

    string show(string cpf){
        stringstream ss;
        float saldoTotal = 0;
        ss << "Cliente: " << cpf << endl;
        for(Cliente c : clientes){
            if(c.getCpf() == cpf){
                contas = c.getConta();
                for(Conta c2 : contas){
                    saldoTotal += c2.getSaldo();
                    ss << "Conta: " << c2.getId() << ", "
                       << "Saldo: " << c2.getSaldo() << ", "
                       << "Status: " << (c2.getAtiva()? "ativa" : "encerrada") << endl;
                }
                ss << "Saldo Total: " << saldoTotal << endl;
                return ss.str();
             }

        }
        return "cliente não logado";
    }
    bool transf(int conta, int outra, float valor){
        vector<Conta> aux;
        vector<int> n;
        vector<string> cpf;
        bool cont1 = false;
        bool cont2 = false;
        for(Cliente c1 : clientes){
            aux = c1.getConta();
            for(Conta c2 : aux)
                n.push_back(c2.getId());
        }
        for(int i = 0; i < (int) n.size(); i++){
            if(n[i] == conta)
                cont1 = true;
            if(n[i] == outra)
                cont2 = true;
        }
        if((cont1 == false) || (cont2 == false))
            return false;
        for(Cliente c3 : clientes){
            vector<Conta> contas = c3.getConta();
            for(Conta c4 : contas){
                if(c4.getId() == conta){
                    if(c4.getAtiva() == false)
                        return false;
                    else
                        cpf.push_back(c3.getCpf());
                }
                if(c4.getId() == outra){
                    if(c4.getAtiva() == false)
                        return false;
                    else
                        cpf.push_back(c3.getCpf());
                }
            }
        }
        for(Cliente& c5 : clientes){
            if(c5.getCpf() == cpf[0]){
                for(Conta& c6 : c5.getConta()){
                    if(c6.getId() == conta){
                        if(valor > c6.getSaldo())
                            return false;
                        c6.sacar(valor);
                        c6.transferir(outra, valor, "para ");
                    }
                }
            }
            if(c5.getCpf() == cpf[1]){
                for(Conta& c7 : c5.getConta()){
                    if(c7.getId() == outra){
                        c7.sacar(-1 * valor);
                        c7.transferir(conta, valor, "de ");
                    }
                }
            }
        }
        return true;
    }
};


void inicializar(Agencia& agencia){
    agencia.addCliente("111");
    agencia.abrirConta("111");
    agencia.abrirConta("111");
    agencia.addCliente("222");
    agencia.abrirConta("222");
    agencia.addCliente("333");
    agencia.abrirConta("333");
}

int main(){
    Agencia agencia;
    Cliente * cliente = nullptr;
    inicializar(agencia);
    string op;
    cout << "digite help" << endl;
    while(op != "fim"){
        cin >> op;

        if(op == "help"){
            cout << "addCli $cpf" << endl
                 << "abrirConta $cpf" << endl
                 << "encerrarConta $conta" << endl
                 << "login $cpf" << endl
                 << "logout" << endl
                 << "showAllCli" << endl
                 << "show" << endl
                 << "saldo $conta" << endl
                 << "saque $conta $valor" << endl
                 << "deposito $conta $valor" << endl
                 << "extrato $conta" << endl
                 << "extratoN $conta $qtd" << endl
                 << "transf $contaDe $contaPara $valor" << endl
                 << "fim" << endl;
        }

        if(op == "addCli"){
            cout << (agencia.addCliente(read<string>())? "Cliente adicionado" : "cpf duplicado") << endl;
        }

        if(op == "abrirConta"){
            int aux = agencia.abrirConta(read<string>());
            if(aux == -1){
                cout << "erro" << endl;
            }else{
                cout << "conta " << aux << " aberta" << endl;
            }

        }

        if(op == "encerrarConta"){
            if(cliente == nullptr)
                cout << "nenhum cliente logado" << endl;
            else{
                int aux = cliente->encerrarConta(read<int>());
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

        if(op == "login"){
            cliente = agencia.Login(read<string>());
            if(cliente == nullptr)
                cout << "cpf invalido" << endl;
            else
                cout << "ok" << endl;
        }

        if(op == "logout"){
            if(cliente == nullptr){
                cout << "nenhum cliente logado" << endl;
            }else{
                cliente = nullptr;
                cout << "ok" << endl;
            }
        }

        if(op == "showAllCli")
            cout << agencia.showAllCli();

        if(op == "show"){
            if(cliente == nullptr)
                cout << "cliente não logado" << endl;
            else
                cout << agencia.show(cliente->getCpf());
        }

        if(op == "saldo"){
            if(cliente == nullptr)
                cout << "nenhum cliente logado" << endl;
            else
                cout << cliente->saldo(read<int>());
        }

        if(op == "saque"){
            int x;
            cin >> x;
            float y;
            cin >> y;
            bool aux = cliente->saque(x,y);
            if(cliente == nullptr)
                cout << "nunhum cliente logado" << endl;
            else
                cout << (aux? "ok" : "erro") << endl;
        }

        if(op == "deposito"){
            int x;
            cin >> x;
            float y;
            cin >> y;
            bool aux = cliente->deposito(x,y);
            if(cliente == nullptr)
                cout << "nunhum cliente logado" << endl;
            else
                cout << (aux? "ok" : "erro") << endl;
        }

        if(op == "extrato"){
            if(cliente == nullptr)
                cout << "nunhum cliente logado" << endl;
            else
                cout << cliente->extrato(read<int>());
        }

        if(op == "extratoN"){
            int x;
            cin >> x;
            int y;
            cin >> y;
            string aux = cliente->extratoN(x, y);
            if(cliente == nullptr)
                cout << "nunhum cliente logado" << endl;
            else
                cout << aux;
        }

        if(op == "transf"){
            int x;
            cin >> x;
            int y;
            cin >> y;
            float z;
            cin >> z;
            bool aux = agencia.transf(x, y, z);
            if(cliente == nullptr)
                cout << "nunhum cliente logado" << endl;
            else{
                cout << (aux? "ok" : "erro") << endl;
            }
        }

    }

}















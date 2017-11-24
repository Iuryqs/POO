#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;

enum FLAG{FONE_ID_JA_EXISTE, NUMERO_INVALIDO, CONTATO_NAO_ENCONTRADO, NOME_NAO_ENCONTRADO, FONE_ID_NAO_EXISTE, NUMERO_ADICIONADO, TELEFONE_REMOVIDO};

template <class T>
T read(){
    T t;
    cin >> t;
    return t;
}

struct Fone{
    string foneId;
    string numero;
    Fone(string foneId = "", string numero = ""){
        this->foneId = foneId;
        this->numero = numero;
    }

    string getFoneId(){
        return foneId;
    }
    string getNumero(){
        return numero;
    }
};


class Contato{
    string nome;
    vector<Fone> fones;
    bool isFavorited{false};
  public:
    Contato(string nome){
        this->nome = nome;
    }

    string getNome(){
        return nome;
    }

    bool addFone(Fone fone){
        fones.push_back(fone);
        return true;
    }

    bool getFavorito(){
        return isFavorited;
    }

    void setFavorito(bool fav){
        this->isFavorited = fav;
    }


    vector<Fone> getFones(){
        return fones;
    }

    bool match(string pattern){
        for(Fone f : fones){
            if(f.getFoneId().find(pattern) != std::string::npos)
                return true;
            else if(f.getNumero().find(pattern) != std::string::npos)
                return true;
        }
        return false;
    }

    bool rmFone(string id){
        for(int i = 0; i < (int) this->fones.size(); i++){
            if(fones[i].getFoneId() == id){
                fones.erase(fones.begin() + i);
                return true;
            }

        }
        return false;
    }

};

bool comparar(Contato x, Contato y){
    return x.getNome() < y.getNome();
}

class Agenda{
    vector<Contato> contatos;
    vector<Contato> favoritos;
  public:
    Agenda(){}

    bool addContato(Contato contato){
        for(Contato c : contatos){
            if(c.getNome() == contato.getNome())
                return false;
        }
        contatos.push_back(contato);
        return true;
    }

    bool rmContato(string nome){
        for(int i = 0; i < (int) contatos.size(); i++){
            if(nome == contatos[i].getNome()){
                contatos.erase(contatos.begin() + i);
                for(int j = 0; j < (int) favoritos.size(); j++)
                    if(nome == favoritos[j].getNome())
                        favoritos.erase(favoritos.begin() + j);
                return true;
            }
        }
        return false;
    }

    string showContatos(){
        stringstream ss;
        std::sort(contatos.begin(), contatos.end(), comparar);
        for(Contato c : contatos){
            vector<Fone> fones = c.getFones();
            if(c.getFavorito()){
                ss << "@ " << c.getNome() << " ";
                for(Fone c2 : fones)
                    ss << "[" << c2.foneId << " " << c2.getNumero() << "] ";
            }else{
                ss << "- " << c.getNome() << " ";
                for(Fone c2 : fones){
                    ss << "[" << c2.foneId << " " << c2.getNumero() << "] ";
                }
            }
            ss << endl;
        }
        return ss.str();
    }

   string search(string pattern){
       stringstream ss;
       for(Contato c : contatos){
           vector<Fone> fones = c.getFones();
           if((c.getNome().find(pattern)) != std::string::npos){
               ss << "- " << c.getNome() << " ";
               for(Fone c2 : fones){
                   ss << "[" << c2.foneId << " " << c2.getNumero() << "] ";
               }
               ss << endl;
           }
           if(c.match(pattern)){
               ss << "- " << c.getNome() << " ";
               for(Fone c2 : fones){
                   ss << "[" << c2.foneId << " " << c2.getNumero() << "] ";
               }
               ss << endl;
           }
       }
       return ss.str();
    }

    bool favoritar(string nome){
        for(Contato& c : contatos){
            if(c.getNome() == nome){
                c.setFavorito(true);
                favoritos.push_back(c);
                return true;
            }
        }
        return false;
    }

    bool desfavoritar(string nome){
        for(Contato& c : contatos){
            if(c.getNome() == nome){
                c.setFavorito(false);
            }
        }
        for(int i = 0; i < (int) favoritos.size(); i++){
            if(favoritos[i].getNome() == nome){
                favoritos.erase(favoritos.begin() + i);
                return true;
            }
        }
        return false;
    }
    string showFav(){
        stringstream ss;
        std::sort(favoritos.begin(), favoritos.end(), comparar);
        for(Contato f : favoritos){
            vector<Fone> fones = f.getFones();
            ss << "@ " << f.getNome() << " ";
            for(Fone f2 : fones)
                ss << "[" << f2.getFoneId() << " " << f2.getNumero() << "] ";
            ss << endl;
        }
        return ss.str();
    }

    FLAG addFone(string nome, string foneId, string numero){
        for(Contato& c : contatos){
            if(c.getNome() == nome){
                vector<Fone> fones = c.getFones();
                for(Fone& f2 : fones){
                    if(f2.getFoneId() == foneId)
                        return FONE_ID_JA_EXISTE;

                    string data = "1234567890()- ";
                    for(auto c : numero)
                        if(data.find(c) == string::npos)
                            return NUMERO_INVALIDO;
                }
                c.addFone(Fone(foneId, numero));
                if(c.getFavorito()){
                    for(int i = 0; i < (int) favoritos.size(); i++){
                        if(favoritos[i].getNome() == nome){
                            favoritos.erase(favoritos.begin() + i);
                            favoritos.push_back(c);
                        }
                    }
                }
                return NUMERO_ADICIONADO;
            }
        }
        return CONTATO_NAO_ENCONTRADO;
    }

    FLAG rmFone(string nome, string foneId){
        for(Contato& c : contatos){
            if(c.getNome() == nome){
                vector<Fone> fones = c.getFones();
                for(Fone& c2 : fones){
                    if(c2.getFoneId() == foneId){
                        c.rmFone(foneId);
                        for(int j = 0; j < (int) favoritos.size(); j++){
                            if(nome == favoritos[j].getNome()){
                                favoritos.erase(favoritos.begin() + j);
                            }
                        }
                        favoritos.push_back(c);
                        return TELEFONE_REMOVIDO;
                    }
                }
                return FONE_ID_NAO_EXISTE;
            }
        }
        return NOME_NAO_ENCONTRADO;
    }

};

void inicializador(Agenda& agenda){
    agenda.addContato(Contato("Iury"));
    agenda.addContato(Contato("Rafa"));
    agenda.addFone("Iury", "tim", "1111");
    agenda.addFone("Iury", "vivo", "2222");
    agenda.addFone("Rafa", "claro", "3333");
}

void interacao(){
    Agenda agenda;
    string op = "";
    inicializador(agenda);
    while(op != "fim"){
        cout << "Digite help ou comando: ";
        cin >> op;
        if(op == "help"){
            cout << "addContato $name" << endl
                 << "rmContato $name" << endl
                 << "addFone $nome $foneid $numero" << endl
                 << "rmFone $nome $foneid" << endl
                 << "showContatos" << endl
                 << "search $pattern" << endl
                 << "fav $nome" << endl
                 << "desfav $nome" << endl
                 << "showFav" << endl
                 << "fim" << endl;
        }

        if(op == "addContato"){
            string nome = read<string>();
            if(agenda.addContato(Contato(nome))){
                cout << "contato adicionado" << endl;
            }else{
                cout << "erro | contato já existe" << endl;
            }
        }

        if(op == "rmContato"){
            if(agenda.rmContato(read<string>())){
                cout << "contato removido" << endl;
            }else
                cout << "erro | contato não existe" << endl;
        }

        if("addFone" == op){
            string nome = read<string>();
            string foneId = read<string>();
            string numero = read<string>();
            FLAG s = agenda.addFone(nome, foneId, numero);
            if(s == FONE_ID_JA_EXISTE)
                cout << "FoneId já existe!" << endl;
            if(s == NUMERO_INVALIDO)
                cout << "Número inválido!" << endl;
            if(s == NUMERO_ADICIONADO)
                cout << "Número adicionado!" << endl;
            if(s == CONTATO_NAO_ENCONTRADO)
                cout << "Contato não encontrado!" << endl;
        }

        if(op == "rmFone"){
            string name = read<string>();
            string foneID = read<string>();
            FLAG s = agenda.rmFone(name, foneID);
            if(s == TELEFONE_REMOVIDO)
                cout << "Telefone removido!" << endl;
            if(s == NOME_NAO_ENCONTRADO)
                cout << "Nome não encontrado!" << endl;
            if(s == FONE_ID_NAO_EXISTE)
                cout << "FoneId não existe!" << endl;
        }

        if(op == "showContatos"){
            cout << agenda.showContatos() << endl;
        }

        if(op == "search"){
            cout << agenda.search(read<string>()) << endl;
        }

        if(op == "fav"){
            string nome = read<string>();
            if(agenda.favoritar(nome))
                cout << nome << "ok" << endl;
            else
                cout << nome << "erro | $nome não encotrado" << endl;
        }

        if(op == "desfav"){
            string nome = read<string>();
            if(agenda.desfavoritar(nome)){
                cout << "ok" << endl;
            }else{
                cout << nome << "erro | $nome não encontrado ou $nome não é favorito" << endl;
            }
        }

        if(op == "showFav"){
            cout << agenda.showFav() << endl;
        }

    }
}

int main()
{
    interacao();
    return 0;
}

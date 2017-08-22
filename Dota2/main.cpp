#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

enum tipo_de_itensv{Tango, Balsamo, Tarrask};
struct Itens_de_vida{
    int valor;
    tipo_de_itensv tipo;

    Itens_de_vida(tipo_de_itensv tipo){
        this->tipo = tipo;
        if(this->tipo == Tango){
            valor = 100;
        }else if(this->tipo == Balsamo){
            valor = 300;
        }else if(this->tipo == Tarrask){
            valor = 500;
        }
    }
};

enum tipo_de_itensm{Mango, Claresa, Pedra};
struct Itens_de_mana{
    int valor;
    tipo_de_itensm tipo;

    Itens_de_mana(tipo_de_itensm tipo){
        this->tipo = tipo;
        if(this->tipo == Mango){
            valor = 100;
        }else if(this->tipo == Claresa){
            valor = 300;
        }else if(this->tipo == Pedra){
            valor = 500;
        }
    }
};

enum tipo_de_itensd{Desoladora, Dedalo, Divine};
struct Itens_de_dano{
    int valor;
    tipo_de_itensd tipo;

    Itens_de_dano(tipo_de_itensd tipo){
        this->tipo = tipo;
        if(this->tipo == Desoladora){
            valor = 100;
        }else if(this->tipo == Dedalo){
            valor = 300;
        }else if(this->tipo == Divine){
            valor = 500;
        }
    }
};

enum tipo_de_heroi{Carry, Suporte, Tanker};
struct Heroi{
    tipo_de_heroi tipo;
    string nome;
    int vida;
    int mana;
    int habilidade;
    int ultimate;
    bool vivo;

    Heroi(string nome, tipo_de_heroi tipo){
        this->nome = nome;
        this->tipo = tipo;
        if(this->tipo == Carry){
        vida = 500 + rand() % 80;
        mana = 200 + rand() % 80;
        habilidade = 90 + rand() % 30;
        ultimate = 150 + rand() % 30;
        }else if(this->tipo == Suporte){
         vida = 400 + rand() % 80;
         mana = 300 + rand() % 80;
         habilidade = 60 + rand() % 30;
         ultimate = 220 + rand() % 30;
        }else if(this->tipo == Tanker){
         vida = 600 + rand() % 80;
         mana = 150 + rand() % 80;
         habilidade = 75 + rand() % 30;
         ultimate = 150 + rand() % 30;
        }
        vivo = true;
    }

    void perder_vida(int valor){
        valor += rand() % 20;
        vida -= valor;
        cout << endl << "Vida perdida igual à: " << valor << endl;
        if(vida < 0)
            vivo = false;
    }

    void perder_mana(int valor){
        valor += rand() % 20;
        mana -= valor;
        cout << endl << "Mana perdida igual à: " << valor << endl;
    }

    void usar_habilidade(Heroi &outro){
        if(mana >= 50){
            cout << endl << nome << " usa sua Habilidade em " << outro.nome << endl;
            if(!outro.vivo){
                cout << endl << "Heroi Morto" << endl;
            }
            outro.perder_vida(habilidade);
            perder_mana(50);
        }else{
            cout << endl << "Sem mana suficiente" << endl;
        }
    }

    void usar_ultimate(Heroi &outro){
        if(mana >= 100){
            cout << endl << nome << " usa sua Ultimate em " << outro.nome << endl;
            if(!outro.vivo){
                cout << endl << "Heroi Morto" << endl;
            }
            outro.perder_vida(ultimate);
            perder_mana(100);
        }else{
            cout << endl << "Sem mana suficiente" << endl;
        }
    }

    void informacao(){
        cout << endl
             << "Nome: " << nome
             << "\nVida: " << vida
             << "\nMana: " << mana
             << "\nValor da habilidade: " << habilidade
             << "\nValor do ultimate: " << ultimate << endl;
    }

    void usar_itemv(Itens_de_vida item){
        vida += item.valor;
        cout << endl << "Heroi " << nome << " ganhou: " << item.valor << " pontos de vida"
        << endl;
    }

    void usar_itemm(Itens_de_mana item){
        mana += item.valor;
        cout << endl << "Heroi " << nome << " ganhou: " << item.valor << " pontos de mana"
        << endl;
    }

    void usar_itemd(Itens_de_dano item){
        habilidade += item.valor;
        ultimate += item.valor;
        cout << endl << "Heroi " << nome << " ganhou: " << item.valor << " pontos de dano"
        << endl;
    }

};

int main(){
    Heroi heroi1 = Heroi("Lina", Carry);
    Heroi heroi2 = Heroi("Crystal", Suporte);
    heroi1.informacao();
    heroi2.informacao();
    heroi1.usar_habilidade(heroi2);
    heroi1.informacao();
    heroi2.informacao();
    heroi2.usar_ultimate(heroi1);
    heroi1.informacao();
    heroi2.informacao();
    Itens_de_vida item1(Tango);
    heroi1.usar_itemv(item1);
    heroi1.informacao();
}

#ifndef DOTA_H
#define DOTA_H
#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <list>

using namespace std;

class Item{
    string nome;
    int valor{0};
    int pVida;
    int pDano;
public:
    Item(string nome = "", int valor = 0){
        this->nome = nome;
        this->valor = valor;
        this->pVida = (valor/2) + rand() % 50;
        this->pDano = (valor/3) + rand() % 50;
    }

    string getNome(){
        return nome;
    }

    int getpVida(){
        return pVida;
    }

    void setpVida(int p){
        pVida = p;
    }

    int getpDano(){
        return pDano;
    }

    void setpDano(int p){
        pDano = p;
    }

    int getValor(){
        return valor;
    }

    void setValor(int v){
        valor = v;
    }

    string toStringItem(){
        stringstream ss;
        ss << "Nome: " << nome << " | Valor: " << valor << endl;
        ss << "pVida: " << pVida << " | pDano: " << pDano << endl;
        return ss.str();
    }


};

class Torre;

class Heroi{
    string nome;
    int gold{0};
    int vida;
    int dano;
    bool vivo;
    vector<Item> item;
    vector<Torre*> torres;
public:
    Heroi(string nome = "",  int gold = 0){
        this->nome = nome;
        this->gold = gold;
        this->vida = 150 + rand() % 100;
        this->dano = 25 + rand() % 50;
        this->vivo = true;
    }

    vector<Torre*> getTorres(){
        return this->torres;
    }

    int getGold(){
        return gold;
    }

    void setGold(int g){
        this->gold = g;
    }

    int getVida(){
        return vida;
    }

    void setVida(int v){
        this->vida = v;
    }

    bool getVivo(){
        return vivo;
    }

    void setVivo(bool v){
        this->vivo = v;
    }

    int getDano(){
        return dano;
    }

    void setDano(int d){
        this->dano = d;
    }

    string getNome(){
        return nome;
    }

    void ComparItem(Item i){
        if(vivo == false)
            throw string("Não pode comprar item, o heroi está morto\n");
        for(auto j : item){
            if(j.getNome() == i.getNome())
                throw string("O heroi já possui esse item\n");
        }
        if(gold >= i.getValor()){
            item.push_back(i);
            gold -= i.getValor();
            vida += i.getpVida();
            dano += i.getpDano();
        }else{
            throw string("Gold Insuficiente\n");
        }
    }

    string farmar(){
        if(vivo == false)
            throw string("Não pode farmar, o heroi está morto\n");
        stringstream ss;
        int g = 50 + rand() % 50;
        gold += g;
        ss << nome << " farmou " << g << ", Agora seu gold é de: " << gold << "." << endl;
        return ss.str();
    }

    void atacarHeroi(Heroi* i){
        if(this->vivo == false)
            throw string("Não pode comprar item, o heroi está morto\n");
        if(i->getVivo() == false)
            throw string("Não se pode atacar um heroi morto\n");
        i->setVida(i->getVida() - this->dano);
        if(i->getDano() > this->dano)
            setVida(this->vida - (i->getDano())/2);
        if(i->getVida() < 0){
            throw string("Heroi nao resistiu ao ataque\n");
            i->setVivo(false);
        }
    }

    string toStringHeroi();
    void addTorres(Torre * torre);
    void atacarTorre(Torre * torre);
    friend class Torre;
    
};

class Torre{
    vector<Heroi*> herois;
    int id;
    int defesa{0};
    bool emPe;
public:
    Torre(int id = 0, int defesa = 0){
        this->id = id;
        this->defesa = defesa;
        this->emPe = true;
    }

    int getId(){
        return this->id;
    }

    bool getemPe(){
        return this->emPe;
    }

    int getDefesa(){
        return this->defesa;
    }

    void setDefesa(int d){
        this->defesa = d;
    }

    void setemPe(bool p){
        this->emPe = p;
    }

    string toStringTorre(){
        stringstream ss;
        ss << "Torre: " << id << " | Defesa: " << defesa << endl;
        ss << "Status: " << emPe << endl;
        ss << "Herois da Torres:" << endl;
        for(auto i : herois)
            ss << i->getNome() << endl;
        return ss.str();
    }

    vector<Heroi*> getHerois(){
        return this->herois;
    }

    void addHeroi(Heroi * heroi){
        herois.push_back(heroi);
        heroi->torres.push_back(this);
    }
};

string Heroi::toStringHeroi(){
    stringstream ss;
    ss << "Nome do Heroi: " << nome << " | Seu Gold: " << gold << endl;
    ss << "Status: " << vivo << endl;
    ss << "Vida: " << vida << " | Dano: " << dano << endl;
    ss << "Itens: " << endl;
    for(auto i : item)
        ss <<  "-" << i.getNome() << endl;
    ss << "Torres do Heroi:" << endl;
    for(auto j : torres)
        ss << j->getId() << endl;
    return ss.str();
}

void Heroi::atacarTorre(Torre * torre){
    if(torre->getDefesa() < 0)
        throw string("Torre ja foi destruida\n");
    if(vivo == false)
        throw string("Não pode atacar, o heroi está morto\n");
    torre->setDefesa(torre->getDefesa() - dano);
    if(torre->getDefesa() < 0){
        torre->setemPe(false);
        throw string("Torre destruida\n");
    }
}

#endif // DOTA_H

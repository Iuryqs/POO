#ifndef DOTA_H
#define DOTA_H
#include <iostream>
#include <vector>
#include <sstream>
#include <list>

using namespace std;

class Item{
    string nome;
    int valor{0};
public:
    Item(string nome = "", int valor = 0){
        this->nome = nome;
        this->valor = valor;
    }

    string getNome(){
        return nome;
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
        return ss.str();
    }


};

class Heroi{
    string nome;
    int gold{0};
    vector<Item> item;
public:
    Heroi(string nome = "",  int gold = 0){
        this->nome = nome;
        this->gold = gold;
    }

    void ComparItem(Item i){
        for(auto j : item){
            if(j.getNome() == i.getNome())
                throw string("O heroi já possui esse item\n");
        }
        if(gold >= i.getValor()){
            item.push_back(i);
            gold -= i.getValor();
        }else{
            throw string("Gold Insuficiente\n");
        }
    }

    string farmar(){
        stringstream ss;
        int g = 50 + rand() % 50;
        gold += g;
        ss << nome << " farmou " << g << ", Agora seu gold é de: " << gold << "." << endl;
        return ss.str();
    }

    int getGold(){
        return gold;
    }

    void setGold(int g){
        gold = g;
    }

    string getNome(){
        return nome;
    }

    string toStringHeroi(){
        stringstream ss;
        ss << "Nome do Heroi: " << nome << " | Seu Gold: " << gold << endl;
        ss << "Itens: " << endl;
        for(auto i : item)
            ss <<  "-" << i.getNome() << endl;
        return ss.str();
    }
    
};

class Loja{
};

#endif // DOTA_H

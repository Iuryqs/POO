#ifndef DOTA_H
#define DOTA_H
#include <iostream>
#include <vector>
#include <sstream>
#include <list>

using namespace std;

class Item{
    string nome;
    int valor;
public:
    Item(string nome = ""){
        this->nome = nome;
    }


};

class Heroi{
    string nome;
    int gold;
    vector<Item> item;
public:
    Heroi(string nome = ""){
        this->nome = nome;
    }
    
};

class Loja{
    Loja(){

    }
};

#endif // DOTA_H

#include <iostream>
#include "dota.h"
#include "poo_aux.h"
#include "poo_repository.h"
#include "poo_controller.h"

using namespace std;
using namespace poo;

string HELP = R"(help
addItem [nome] [valor]
showItens
dadosItem [nome]
addHeroi [nome] [gold]
showHerois
dadosHeroi [nome]
farmar [nome_do_heroi]
comprarItem [nome_do_heroi] [nome_do_item]
fim
)";

class Dota : public Controller{
    Repository<Heroi> heroi;
    Repository<Item> item;

public:
    Dota(): heroi("heroi"), item("item"){
    }

    string process(string line){
        auto ui = poo::split(line, ' ');
        auto cmd = ui[0];

        if(cmd == "help")
            return HELP;
        else if(cmd == "addItem"){
            item.add(ui[1], Item(ui[1], Int(ui[2])));
        }
        else if(cmd == "showItens"){
            return "" + item.keys();
        }
        else if(cmd == "dadosItem"){
            return item.get(ui[1])->toStringItem();
        }
        else if(cmd == "addHeroi"){
            heroi.add(ui[1], Heroi(ui[1], Int(ui[2])));
        }
        else if(cmd == "showHerois"){
            return "" + heroi.keys();
        }
        else if(cmd == "dadosHeroi"){
            return heroi.get(ui[1])->toStringHeroi();
        }
        else if(cmd == "farmar"){
            return heroi.get(ui[1])->farmar();
        }
        else if(cmd == "comprarItem"){
            heroi.get(ui[1])->ComparItem(item.at(ui[2]));
        }
        else if(cmd == "fim")
            return "";
        else
            return string("") + "comando invalido " + "[" + cmd + "]";
        return "done";
    }
};


int main(){
    Dota c;
    c.commandLine();
    return 0;
}

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
addTorre [id] [defesa]
showTorres
dadosTorre [id]
farmar [nome_do_heroi]
comprarItem [nome_do_heroi] [nome_do_item]
atacarHeroi [nome_do_heroi] [nome_do_heroi_atacado]
atacarTorre [nome_do_heroi] [id_torre]
relacionarTorre [id_torre] [nome_do_heroi]
fim
)";

class Dota : public Controller{
    Repository<Heroi> heroi;
    Repository<Item> item;
    Repository<Torre> torre;

public:
    Dota(): heroi("heroi"), item("item"), torre("torre"){
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
        else if(cmd == "addTorre"){
            torre.add(ui[1], Torre(Int(ui[1]), Int(ui[2])));
        }
        else if(cmd == "showTorres"){
            return "" + torre.keys();
        }
        else if(cmd == "dadosTorre"){
            return torre.get(ui[1])->toStringTorre();
        }
        else if(cmd == "farmar"){
            return heroi.get(ui[1])->farmar();
        }
        else if(cmd == "comprarItem"){
            heroi.get(ui[1])->ComparItem(item.at(ui[2]));
        }
        else if(cmd == "atacarHeroi"){
            heroi.get(ui[1])->atacarHeroi(heroi.get(ui[2]));
        }
        else if(cmd == "atacarTorre"){
            heroi.get(ui[1])->atacarTorre(torre.get(ui[2]));
        }
        else if(cmd == "relacionarTorre"){
            torre.get(ui[1])->addHeroi(heroi.get(ui[2]));
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

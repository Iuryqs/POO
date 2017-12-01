#include <iostream>
#include "dota.h"
#include "poo_aux.h"
#include "poo_repository.h"
#include "poo_controller.h"

using namespace std;
using namespace poo;

string HELP = R"(help
addHeroi [nome]
addItem [nome]
showHerois
showItens
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
        else if(cmd == "addHeroi"){
            for(int i = 1; i < (int) ui.size(); i++){
                heroi.add(ui[i],Heroi(ui[i]));
            }
        }
        else if(cmd == "addItem"){
            for(int i = 1; i < (int) ui.size(); i++){
                item.add(ui[i],Item(ui[i]));
            }
        }
        else if(cmd == "showHerois"){
            return "" + heroi.keys();
        }
        else if(cmd == "showItens"){
            return "" + item.keys();
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

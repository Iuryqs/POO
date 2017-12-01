#ifndef CONTROLLER
#define CONTROLLER
#include "dota.h"
#include <sstream>


string HELP = R"(
help
addUser    _nome
        )";

class Controller{
    int nextId{0};
public:
    Controller(){

    }

    string process(string line){
        auto ui = split(line);
        auto cmd = ui[0];

        if(cmd == "help") return HELP;

        if(cmd == "addUser"){
            r_user.add(ui[1], User(ui[1]));
            return "Usuário Criado!\n";
        }
};
#endif // CONTROLLER


#ifndef WHATSAPP_H
#define WHATSAPP_H

#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include "poo_aux.h"

using namespace std;
using namespace poo;

class Zap{
private:
    string userID;
    string msg;
public:
    Zap(string userID = "", string msg = ""){
        this->userID = userID;
        this->msg = msg;
    }

    string toString(){
        stringstream ss;
        ss << "[" << userID << ":" << msg << "]" << endl;
        return ss.str();
    }

    string getuserId(){
    return this->userID;
    }

};

class Chat;

class User{
private:
  map<string, Chat*> lista_chat;
  string userId;
public:
  User(string userId = ""){
      this->userId = userId;
  }

  vector<string> getChats(){
      return poo::map_keys(lista_chat);
  }

  void assertChat(string chatId){
      auto i = lista_chat.count(chatId);
      if(i == 0)
          throw "O usuário não ta no chat";

  }

  string toString(){
      return this->userId;
  }

  string getOverview();

  void invite(string chatId, User* user);

  void leave(string chatId);

  void sendZap(string msg, string chatId);

  friend class Chat;

};

class Registro{
private:
    User * user;
    int unreadCount{0};
public:
    Registro(User * user = nullptr){
        this->user = user;
    }
    int getunreadCount(){
        return this->unreadCount;
    }
    void setunreadCount(int x){
        this->unreadCount = x;
    }
    void unreadCountAdd(int x){
        this->unreadCount += x;
    }
};

class Chat{
private:
    string chatId;
    vector<Zap> lista_zap;
    map<string, Registro> lista_reg;
    string systemUsername = "system";
public:
    Chat(string chatId = ""){
        this->chatId = chatId;
    }

    bool addFirstUser(User * chatCreator){
        if(((int)lista_reg.size()) != 0)
            throw "Erro - Chat já existe";
        lista_reg[chatCreator->userId] = Registro(chatCreator); //add o usuario
        chatCreator->lista_chat[this->chatId] = this; //se adicionando
        return true;
    }

    vector<string> getUsers(){
        vector<string> aux;
        for(auto i : lista_reg)
            aux.push_back(i.first);
        return aux;
    }

    void assertUser(string user){
        auto i = lista_reg.count(user);
        if(i == 0)
            throw "O usuário não existe";

    }

    void deliverZap(Zap zap){
        if(zap.getuserId() == systemUsername){//mensagem do sistema
            lista_zap.push_back(zap);
            for(auto i : lista_reg)
                i.second.unreadCountAdd(1);
        }else{
            assertUser(zap.getuserId());
            lista_zap.push_back(zap);
            for(auto& i : lista_reg)
                if(i.first != zap.getuserId())
                    i.second.unreadCountAdd(1);
        }
    }

    int getUnreadCount(string userId){
        assertUser(userId);
        Registro i = lista_reg[userId];
        return i.getunreadCount();
    }

    vector<Zap> getUnread(string userId){
//        assertUser(userId);
//        vector<Zap> aux;
//        if(getUnreadCount(userId) == 0)
//            throw "Nao existe mensagem para ler";
//        for(auto i : lista_zap){
//            if(i.userID == userId)
//                aux.push_back(i.msg);
//        }


    }

    bool hasUser(string userId){
        if(lista_reg.count(userId))
            return true;
        return false;
    }

    string toString(){
        return this->chatId;
    }




    friend class User;

};

string User::getOverview(){
    stringstream ss;
    for(auto i : lista_chat)
        ss << "Chat: " << i.first << "[" << i.second->getUnreadCount(userId) << "]" << endl;
    return ss.str();
}


#endif // WHATSAPP_H

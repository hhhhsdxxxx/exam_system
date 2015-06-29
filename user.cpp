#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include "user.h"

using namespace std;

std::map<std::string, info>* user::whole;

int user::login(){
    auto it = user::whole->find(this->id);
    if((it->second).pwd == this->pwd)
        return (it->second).type;
    return -1;
}

bool user::change(string uid, string opwd, string npwd){
    auto it = user::whole->find(uid);
    //cout << uid << "gggg" << endl;
    //return true;
    if((it->second).pwd != opwd)
        return false;
    int type = (it->second).type;
    //return true;
    user::whole->erase(it);
    //return true;
    user::whole->insert(pair<string, info>(uid, info(npwd, type)));
    return true;
}

void user::load(){
    whole = new map<string ,info>;
    ifstream fin("user.txt", ios::in);
    string id, pwd;
    //fin >> id;
    int type = -1;
    while(fin >> id){
        fin >> pwd >> type;
        //QMessageBox::about(this, id, pwd);
        //cout << id << " " << pwd << " " << type << endl;
        //cout << this->id << " " << this->pwd << " " << type << endl;
        whole->insert(pair<string, info>(id ,info(pwd, type)));
    }
    fin.close();
}

void user::write_back(){
    ofstream fout("user.txt", ios::ate);
    for(auto it = whole->begin(); it != whole->end(); ++it)
        fout << it->first << " " << (it->second).pwd << " " << (it->second).type << endl;
    user::whole->erase(user::whole->begin(), user::whole->end());
    fout.close();
}

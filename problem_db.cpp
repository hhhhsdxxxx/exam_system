#include "problem_db.h"
#include <iostream>
#include <map>
#include <fstream>

using namespace std;

bool problem_db::add(int id, string filename){
    auto it = mymap->find(id);
    if(it != mymap->end())
        return false;
    ifstream fin;
    fin.open(filename, ios::in);
    if(!fin)
        return false;
    else{
        int num;
        fin >> num;
        total+=num;
        fin.close();
    }
	mymap->insert(pair<int, string>(id, filename));
    return true;
}

void problem_db::remove(int key){
    auto it = mymap->find(key);
    if(it == mymap->end())
        return;
    ifstream fin;
    fin.open(it->second, ios::in);
    int num;
    fin >> num;
    total-=num;
    fin.close();
	mymap->erase(key);
}

void problem_db::readin(){
    ifstream fin("index.txt", ios::in);
    fin >> total;
    int id;
    string filename;
    while(fin >> id){
        fin >> filename;
        add(id, filename);
    }
    fin.close();
}

void problem_db::writeout(){
    ofstream fout("index", ios::out | ios::ate);
    fout << total << endl;
    for(auto it : *mymap)
        fout << it.first << " " << it.second << "\n";
    fout.close();
}

string problem_db::find(int key){
    auto it = mymap->find(key);
    if(it == mymap->end())
        return "";
    return it->second;
}

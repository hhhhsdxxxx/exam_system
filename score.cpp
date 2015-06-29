#include <iostream>
#include <fstream>
#include "score.h"

using namespace std;

list<pair<int, int>>* score::get(){
    ifstream fin;
    fin.open(user_name+"s", ios::in);
    if(!fin)
        return NULL;
    list<pair<int, int>> *re = new list<pair<int,int>>;
	int eid, escore;
	while(fin >> eid >> escore)
        re->push_back(pair<int, int>(eid, escore));
	fin.close();
	return re;
}

void score::write(int eid, int escore){
    ifstream fin;
    fin.open(user_name+"s", ios::in);
    if(!fin){
        ofstream ff(user_name+"s", ios::out);
        ff.close();
    }
    ofstream fout(user_name+"s", ios::out|ios::app|ios::ate);
	fout << eid << " " << escore << "\n";
	fout.close();
}

bool score::is_taken(int eid){
    ifstream fin;
    fin.open(user_name+"s", ios::in);
    if(!fin)
        return false;
    int idd, score;
    while(fin >> idd){
        fin >> score;
        if(idd == eid)
            return true;
    }
    return false;
}

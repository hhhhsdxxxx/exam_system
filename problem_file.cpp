#include "problem_file.h"
#include <iostream>
#include <map>
#include <fstream>

using namespace std;

void problem_file::read_in(){
	ifstream fin(filename, ios::in);
	int type, id, ans;
    fin >> total >> fid >> id >> type >> ans;
	string buffer, comment;
	while(getline(fin, buffer)){
		if(buffer == "----"){
            problem *ptr;
			if(type == 1){
                ptr = new judgement;
				ptr->set_problem(comment);
			}
			else if(type == 2){
                ptr = new selection;
				ptr->set_problem(comment);
			}
			ptr->set_answer(ans);
			mymap->insert(pair<int, problem*>(id, ptr));
			fin >> id >> type >> ans;
            comment = "";
		}
		else{
			comment += buffer+"\n";
		}
	}
	fin.close();
}

void problem_file::write_back(){
	if(mymap == NULL)
		return;
    ofstream fout(filename, ios::out | ios::ate);
    fout << total << " " << fid << endl;
    for(auto it = mymap->begin(); it != mymap->end(); ++it){
        problem *ptr = it->second;
        fout << it->first << " " << ptr->Type() << " " << ptr->show_answer()
			 << ptr->show_comment() << "----" << endl;
        //delete ptr;
	}
    mymap->erase(mymap->begin(), mymap->end());
	mymap = NULL;
	fout.close();
}

bool problem_file::add(int id, problem *pro){
    if(total == 100)
        return false;
    if(id == -1)
        id = total+fid;
    else {
        auto it = mymap->find(id);
        if(it == mymap->end())
            return false;
    }
	mymap->insert(pair<int, problem*>(id, pro));
    total++;
    return true;
}

void problem_file::remove(int key){
	mymap->erase(key);
    total--;
}

problem* problem_file::get(int key){
    auto it = mymap->find(key);
    if(it == mymap->end())
        return NULL;
    return it->second;
}

problem_file::~problem_file(){
    //write_back();
    filename = "";
}

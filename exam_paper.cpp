#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "exam_paper.h"

using namespace std;
vector<problem*> exam_paper::mypro;

void exam_paper::add(selection *sel){
	if(!pro)
		pro = new problem*[num_pro];
	if(element == num_pro)
		return; 
	pro[element++] = sel;
	total += sel->tscore();
}

void exam_paper::add(judgement *jud){
	if(!pro)
		pro = new problem*[num_pro];
	if(element == num_pro)
		return; 
	pro[element++] = jud;
	total += jud->tscore();
}

void exam_paper::remove(int i){
	if(!pro || i >= element)
		return;
	delete pro[i];
	pro[i] = 0;
}

void exam_paper::givescore(int pos, int ans){
    //int last = pro[pos]->hscore();
    pro[pos]->judge(ans);
    //if(!last)
    gets += pro[pos]->hscore();
//    else {
//        if(!(pro[pos]->hscore()))
//            gets -= last;
//    }
}

//bool exam_paper::write_to_file(){
//	char name[20];
//    sprintf_s(name, "%dt", ID);
//    ifstream fin;
//    fin.open(name, ios::in);
//    if(!fin)
//        return false;
//	ofstream fout(name, ios::out);
//	fout << total << " " << num_pro << endl;
//	for(int i = 0; i < num_pro; i++)
//		fout << pro[i]->Type() << endl << pro[i]->show_comment() << "----" << endl;
//	fout.close();
//    sprintf_s(name, "%da", ID);
//	fout.open(name, ios::out);
//	for(int i = 0; i < num_pro; i++)
//		fout << pro[i]->show_answer() << " ";
//    fout.close();
//    return true;
//}

bool exam_paper::read_from_file(){
	char name[20];
    sprintf_s(name, "%dt", ID);
    ifstream fin;
    fin.open(name, ios::in);
    if(!fin)
        return false;
	string buffer, comment;
	fin >> total >> num_pro;
    pro = new problem*[num_pro];
	int type;
	fin >> type;
	while(getline(fin, buffer)){
		if(buffer == "----"){
			if(type == 1)
				pro[element] = new judgement;
			else if(type == 2)
				pro[element] = new selection;
            pro[element]->set_problem(comment);
			comment = "";
			fin >> type;
			element++;
		}
		else{
			comment += buffer+"\n"; 
		}
	}
	fin.close();
    sprintf_s(name, "%da", ID);
	fin.open(name, ios::in);
	int ans;
	element = 0;
	while(fin>>ans)
		pro[element++]->set_answer(ans);
    for(int i = 0; i < num_pro; i++)
        cout << pro[i]->show_answer() << "\n";
	fin.close();
    return true;
}

problem* exam_paper::get(int i){
    return pro[i];
}

exam_paper::~exam_paper(){
	for(int i = 0; i < num_pro; i++)
		delete pro[i];
	delete[] pro;
}

void exam_paper::add(problem* p){
    exam_paper::mypro.push_back(p);
}

void exam_paper::removes(int i){
    exam_paper::mypro.erase(mypro.begin()+i);
}

bool exam_paper::write_to_file(std::string filename){
//    ifstream fin;
//    fin.open(filename+"t", ios::in);
//    if(!fin)
//        return false;
//    else
//        fin.close();
    ofstream fout_t(filename+"t", ios::out);
    ofstream fout_s(filename+"a", ios::out);
    int total = 0;
    for(auto it = exam_paper::mypro.begin(); it != exam_paper::mypro.end(); ++it)
        total += (*it)->tscore();
    fout_t << total << " ";
    total = (int)exam_paper::mypro.size();
    fout_t << total << "\n";
    for(auto it = exam_paper::mypro.begin(); it != exam_paper::mypro.end(); ++it){
        fout_t << (*it)->Type() << "\n" << (*it)->show_comment() << "\n" << "----" << "\n";
        fout_s << (*it)->show_answer() << " ";
    }
    fout_t.close();
    fout_s.close();
//    for(auto it = mypro.begin(); it != mypro.end(); it++)
//        delete *it;
//    exam_paper::mypro.erase(exam_paper::mypro.begin(), exam_paper::mypro.end());
    return true;
}

problem* exam_paper::get_m(int i){
    if(i > (int)mypro.size() || i < 0)
        return NULL;
    return mypro.at(i);
}

void exam_paper::give_up(){
    for(auto it = mypro.begin(); it != mypro.end(); it++)
        delete *it;
    mypro.erase(mypro.begin(), mypro.end());
}

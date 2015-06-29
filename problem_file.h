#ifndef _PROBLEM_FILE_H_
#define _PROBLEM_FILE_H_

#include <map>
#include <string>
#include "problem.h"
#include "judgement.h"
#include "selection.h"

class problem_file{
	std::string filename;
    int total, fid;
    std::map<int, problem*> *mymap;
public:
    problem_file(std::string name):filename(name){ mymap = new std::map<int, problem*>; }
	void read_in();
	void write_back();
    bool add(int id, problem *pro);
	void remove(int key);
    std::string Name() const { return filename; }
	problem* get(int key);
	~problem_file();	
};

#endif

#ifndef _PROBLEM_DB_H
#define _PROBLEM_DB_H

#include <map>
#include <string>

class problem_db{
    std::map<int, std::string> *mymap;
    int total;
public:
    problem_db():total(0){ mymap = new std::map<int, std::string>; }
    bool add(int id, std::string filename);
	void remove(int key);
	void readin();   //index file
	void writeout();  //index file
    std::map<int, std::string> *getdb() const{ return mymap; }
    std::string find(int key);
	~problem_db(){ delete mymap; }
};

#endif

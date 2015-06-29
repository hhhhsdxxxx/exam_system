#ifndef _EXAMPAPER_H_
#define _EXAMPAPER_H_

#include "problem.h"
#include "judgement.h"
#include "selection.h"
#include <vector>
#include <string>

class exam_paper{
	problem **pro;
	int total, gets, num_pro, element, ID;
    static std::vector<problem*> mypro;
public:
    exam_paper():total(0),gets(0),num_pro(0),pro(NULL),element(0),ID(0){}
    exam_paper(int eID):total(0),gets(0),num_pro(0),pro(NULL),element(0),ID(eID){}
	void set_num(int num){ num_pro = num; }
	void set_id(int id){ ID = id; }
	void add(selection *sel);
	void add(judgement *jud);
	void remove(int i);
    void givescore(int pos, int ans);
    //bool write_to_file();
    bool read_from_file();
    int numbers() const { return num_pro; }
    int getID() const { return ID; }
    int result() const { return gets; }
    static void add(problem* p);
    static void removes(int i);
    static bool write_to_file(std::string filename);
    static problem* get_m(int i);
    static void give_up();
    problem *get(int i);
	~exam_paper();
};

#endif

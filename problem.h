#ifndef _PROBLEM_H_
#define _PROBLEM_H_

#include <string>

const int FULL = 10;
const int HALF = 5;
const int ZERO = 0;
class problem{
	int score, h_score;
    bool is_judge;
    std::string comment;
public:
    problem():score(4),h_score(0),comment(""),is_judge(false){}
    problem(int sco):score(sco),h_score(0),comment(""),is_judge(false){}
    int tscore() const { return score; }
    int hscore() const { return h_score; }
    std::string show_comment() const{ return this->comment; }
    void set_problem(std::string s){ comment = s; }
    virtual int Type()=0;
    virtual int show_answer()=0;
    virtual bool judge(int in)=0;
    virtual void set_answer(int i)=0;
    void set_score(int d);
    bool isdone() const { return is_judge; }

protected: 
	bool give_score(int d);
};

#endif

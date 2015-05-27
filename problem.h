#ifndef _PROBLEM_H_
#define _PROBLEM_H_

#include <string>

const int FULL = 10;
const int HALF = 5;
const int ZERO = 0;

class problem{
	int score, h_score;
	string comment;
public:
	problem():score(0),h_score(0),comment(""){}
	problem(int sco, int h_sco):score(sco),h_score(h_sco),comment(""){}
	void set_problem(string s){ comment = s; }
	virtual bool judge(int in()){};
	void set_score(int d);

protected: 
	bool give_score(int d);
};

#endif
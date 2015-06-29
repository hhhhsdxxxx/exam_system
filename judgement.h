#ifndef _JUDGEMENT_H_
#define _JUDGEMENT_H_

#include "problem.h"

class judgement : public problem{
	int ans;
public:
	judgement():ans(-1){}
    judgement(int a):ans(a){}
	void set_answer(int i);
    bool judge(int in);
	int show_answer(){ return ans; }
	int Type(){ return 1; }
};

#endif

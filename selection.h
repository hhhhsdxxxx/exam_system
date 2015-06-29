#ifndef _SELECTION_H_
#define _SELECTION_H_
#include "problem.h"
#include <string>

class selection : public problem{
	int answer;
public:
	selection():answer(-1){}
    selection(int ans):answer(ans){}
	//bool set_selection(int i, string content);
    void set_answer(int i);
    bool judge(int in);
	int show_answer(){ return answer; }
	int Type(){ return 2; }
};
#endif

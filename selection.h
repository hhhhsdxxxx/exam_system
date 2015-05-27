#ifndef _SELECTION_H_
#define _SELECTION_H_

#include <string>

class selection : public problem{
	int answer, choice;
	string *a;
public:
	problem(int c):answer(-1),choice(c),a(0){}
	problem()answer(-1),choice(-1),a(0){}
	bool set_selection(int i, string content);
	bool set_answer(int i);
	bool judge(int in);

	~problem();
};
#endif
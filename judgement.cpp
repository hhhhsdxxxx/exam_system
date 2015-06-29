#include <iostream>
#include "judgement.h"
#include "problem.h"

void judgement::set_answer(int i){
	this->ans = i;
}

bool judgement::judge(int in){
	if(in == ans)
		return give_score(FULL);
	else
        return give_score(ZERO);
}

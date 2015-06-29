#include <iostream>
#include <string>
#include "selection.h"
#include "problem.h"

void selection::set_answer(int i){
    answer = i;
}

bool selection::judge(int in){
    if(in == answer)
		return give_score(FULL);
	else
		return give_score(ZERO);
}

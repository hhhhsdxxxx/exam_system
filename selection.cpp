#include <iostream>
#include <string>
#include "selection.h"
#include "problem.h"

bool selection::set_selection(int i, string content){
	if(i > choice || choice == -1)
		return false;
	if(!a)
		a = new string[choice];
	a[i-1] = content;
	return true;
}

bool selection::set_answer(int i){
	if(i > choice || choice == -1)
		return false;
	answer |= 1 << i;
	return true;
}

bool selection::judge(int in){
	if(i > choice || choice == -1)
		return false;
	if(in & answer)
		return give_score(FULL);
	else
		return give_score(ZERO);
}
#include <iostream>
#include "problem.h"

void problem::set_score(int d){
	score = d;
}

bool problem::give_score(int d){
	if(d > 10 || d < -1)
		return false;
	h_score = d*score/10;
	return true;
}


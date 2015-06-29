#ifndef _SCORE_H_
#define _SCORE_H_

#include <list>
#include <string>

class score{
    std::string user_name;
public:
    score(std::string name){ user_name = name; }
	std::list<std::pair<int, int>> *get();
	void write(int eid, int escore);
    bool is_taken(int eid);
};

#endif

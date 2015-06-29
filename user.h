#ifndef _USER_H_
#define _USER_H_

#include <string>
#include <map>

struct info{
    std::string pwd;
    int type;
    info(std::string ppwd, int ttype):pwd(ppwd),type(ttype){}
};

class user{
    std::string id, pwd;
    static std::map<std::string, info> *whole;
public:
    user(std::string log_id, std::string login_pwd):id(log_id),pwd(login_pwd){}
    int login();
    static bool change(std::string uid, std::string opwd, std::string npwd);
    static void load();
    static void write_back();
};

#endif

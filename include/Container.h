// Container.h
#ifndef CONTAINER_H
#define CONTAINER_H
#include <iostream>

class Container{
private:
    int type;
    char icon;
    std::string name, value;
    Container *next, *child;
public:
    Container(int _type, char _icon, std::string _name);
    Container* get_next();
    Container* get_child();
    std::string get_value();
    std::string get_name();
    void set_next(Container *_next);
    void set_child(Container *_child);
    void set_value(std::string x);
    void draw();
};

#endif
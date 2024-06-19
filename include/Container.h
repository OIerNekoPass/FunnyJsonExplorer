// Container.h
#ifndef CONTAINER_H
#define CONTAINER_H
#include <iostream>

class Container{
private:
    int type;
    std::string icon;
    std::string name, value;
    Container *next, *child;
public:
    Container(int _type, std::string _icon, std::string _name);
    Container* get_next();
    Container* get_child();
    std::string get_value();
    std::string get_name();
    void set_next(Container *_next);
    void set_child(Container *_child);
    void set_value(std::string x);
    void draw();
};

class Visitor{
private:
    Container *p;
public:
    void set_contain(Container *q);
    void set_next(Container *q);
    void set_child(Container *_child);
    void set_value(std::string x);
}

#endif
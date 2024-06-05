#include "Container.h"

Container::Container(int _type, char _icon, std::string _name){
    type = _type;
    icon = _icon;
    name = _name;
    value = "";
    child = next = nullptr;
}
Container* Container::get_next(){
    return next;
}
Container* Container::get_child(){
    return child;
}
std::string Container::get_value(){
    return value;
}
std::string Container::get_name(){
    return name;
}
void Container::set_next(Container *_next){
    next = _next;
}
void Container::set_child(Container *_child){
    child = _child;
}
void Container::set_value(std::string x){
    value = x;
}
void Container::draw(){
    printf ("%c%s", icon, name.c_str());
    if (type == 2 || type > 4) printf (" ");
    else printf (": %s ", value.c_str());
}
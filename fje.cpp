#include <iostream>
#include <cstdio>
#include "FunnyjsonExplorer.h"

void usage(bool err = 1){
    if (err) puts("ERROR: Please check your command format.");
    puts("Use: fje -f <json file> [-s <style>] [-i <icon family>]");
    puts("<style>: 1. tree");
    puts("         2. rectangle");
    puts("<icon family>: two different char for inside node and leaf node");
    return ;
}

int main(int argc, char *argv[]){
    std::string cmd;
    bool valid = false;
    std::string file_name, style = "tree";
    char node_icon = ' ', leaf_icon = ' ';
    
    // get info
    for (int i = 1; i < argc; ++i){
        cmd = argv[i];
        if (cmd == "-f"){
            file_name = argv[++i];
            valid = true;
        }
        else if (cmd == "-s"){
            style = argv[++i];
        }
        else if (cmd == "-i"){
            node_icon = argv[++i][0];
            leaf_icon = argv[++i][0];
        }
        else if (cmd == "-help" || cmd == "-h"){
            usage(0);
            return 0;
        }
        else{
            usage();
            return 0;
        }
    }
    
    // command have no file_name
    if (valid == false){
        usage();
        return 0;
    }

    FunnyjsonExplorer *test;
    if (style == "tree") test = new TreeStyleFactory();
    else if (style == "rectangle") test = new RectangleStyleFactory();
    else{
        puts("style not found.");
        return 0;
    }

    test->set_icon(node_icon, leaf_icon);
    test->_load(file_name);
    test->show();

    return 0;
}
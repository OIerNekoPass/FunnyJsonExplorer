#include <iostream>
#include <cstdio>
#include <fstream>
#include "../include/FunnyjsonExplorer.h"

void usage(bool err = 1){
    if (err) puts("ERROR: Please check your command format.");
    puts("Usage: fje -f <json file> [-s <style>] [-i <icon family>] [-h | -help]");
    puts("<style>: 1. tree");
    puts("         2. rectangle");
    puts("<icon family>: icon family name in file icon.json, use default icon family if empty.");
    puts("-h | -help: see how to use fje.");
    return ;
}

std::string node_icon, leaf_icon;

bool check_icon(std::string icon_family){
    std::string json_info, tmp;
    std::ifstream fin;
    fin.open("icon.json");
    if (!fin.is_open()){
        std::cout<< "Cannot open file: json.icon" << std::endl;
        return false;
    }
    while(getline(fin, tmp)){
        json_info += tmp;
        json_info += "\n";
    }
    fin.close();
    
    auto parser = cJSON_Parse(json_info.c_str());
    if (parser == nullptr){
        puts("icon.json is not a legal json file.");
        return false;
    }

    auto icons =  cJSON_GetObjectItem(parser, icon_family.c_str());
    if (icons == NULL){
        printf("icon family %s not found in icon.json.\n", icon_family.c_str());
        return false;
    }
    auto node = cJSON_GetObjectItem(icons, "node");
    if (node == NULL || node.type != 4){
        printf("icon family %s does not have string member \"node\" in icon.json.\n", icon_family.c_str());
        return false;
    }
    auto leaf = cJSON_GetObjectItem(icons, "leaf");
    if (leaf == NULL || leaf.type != 4){
        printf("icon family %s does not have string member \"leaf\" in icon.json.\n", icon_family.c_str());
        return false;
    }

    node_icon = node.valuestring;
    leaf_icon = leaf.valuestring;

    return true;
}

int main(int argc, char *argv[]){
    std::string cmd;
    bool valid = false;
    std::string file_name, style = "tree";
    
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
            if (!check_icon(argv[++i])){
                printf("icon family name: %s not found in icon.json.\n");
                puts("icon family format in icon.json should be:");
                puts("{");
                puts("    \"<icon family name>\" : {");
                puts("        \"leaf\" : \"1\",");
                puts("        \"node\" : \"2\"");
                puts("    }");
                puts("}");
                return 0;
            }
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
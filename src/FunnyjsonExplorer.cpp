#include "../include/FunnyjsonExplorer.h"
#include <fstream>
#define rec_width 8
//rec_width 为矩形右边保留宽度

bool FunnyjsonExplorer::_load(std::string file){
    std::string json_info, tmp;
    std::ifstream fin;
    fin.open(file);
    if (!fin.is_open()){
        std::cout<< "Cannot open file: " << file << std::endl;
        return false;
    }
    while(getline(fin, tmp)){
        json_info += tmp;
        json_info += "\n";
    }
    fin.close();
    
    auto parser = cJSON_Parse(json_info.c_str());
    if (parser == nullptr){
        puts("Not a legal json file.");
        return false;
    }

    json_tree = json_to_container(parser->child);
    return true;
}

Container* FunnyjsonExplorer::json_to_container(cJSON *parser){
    std::string icon = (parser->child == nullptr ? leaf_icon : node_icon); // 设置icon
    auto node = new Container(parser->type, icon, parser->string); // 创建节点

    // 遍历
    if (parser->child != nullptr) node->set_child(json_to_container(parser->child));
    else{ // 若为叶子节点
        if (parser->type == 0) node->set_value("True");
        else if (parser->type == 1) node->set_value("False");
        else if (parser->type == 3) node->set_value(std::to_string(parser->valueint));
        else if (parser->type == 4) node->set_value(parser->valuestring);
    }
    if (parser->next != nullptr) node->set_next(json_to_container(parser->next));

    return node;
}

void FunnyjsonExplorer::set_icon(std::string ni, std::string li){
    node_icon = ni;
    leaf_icon = li;
}

bool StyleFactory::tryStyle(string _style){
    if (_style == "tree") return true;
    else if (_style == "rectangle") return true;
    else return false;
}

StyleFactory* StyleFactory::getStyle(string _style){
    if (_style == "tree"){
        auto p = new TreeStyleFactory();
        return p;
    }
    else if (_style == "rectangle"){
        auto p = new RectangleStyleFactory();
        return p;
    }
    return NULL;
}

void TreeStyleFactory::show(){
    dfs(json_tree);
}
void TreeStyleFactory::dfs(Container *it){
    for(auto i: stack){
        if (i == false) printf("   ");
        else printf("│  ");
    }

    stack.push_back(it->get_next() != nullptr);
    if (stack.back()) printf("├─");
    else printf("└─");
    it->draw();
    printf("\n");

    if (it->get_child() != nullptr) dfs(it->get_child());
    stack.pop_back();

    if (it->get_next() != nullptr) dfs(it->get_next());
}


void RectangleStyleFactory::show(){
    max_length = json_size = output_count = 0;
    get_rec_info(json_tree, 0);
    dfs(json_tree, 0);
}
void RectangleStyleFactory::get_rec_info(Container *it, int dep){
    json_size++; // 统计json键值对个数 用于判断上下底边
    int len = (dep + 1) * 3 + it->get_name().length() + it->get_value().length() + 1;
    if (it->get_value().length() != 0) len += 2; // 统计最长长度，用于设置矩形宽度

    max_length = (len > max_length ? len : max_length);
        
    if (it->get_child() != nullptr) get_rec_info(it->get_child(), dep + 1);
    if (it->get_next() != nullptr) get_rec_info(it->get_next(), dep);
}
void RectangleStyleFactory::dfs(Container *it, int dep){
    int len = (dep + 1) * 3 + it->get_name().length() + it->get_value().length() + 1;
    if (it->get_value().length() != 0) len += 2; // 统计最长长度，用于设置矩形宽度
    
    output_count ++;
    if (output_count == 1){
        printf("┌─");
        it->draw();
        for (int i = len; i < max_length + rec_width; ++i) printf("─");
        printf("┐\n");
    }
    else if (output_count == json_size){
        printf("└─");
        for (int i = 0; i < dep; ++i) printf("─┴─");
        it->draw();
        for (int i = len; i < max_length + rec_width; ++i) printf("─");
        printf("┘\n");
    }
    else{
        for (int i = 0; i < dep; ++i) printf("│  ");
        printf("├─");
        it->draw();
        for (int i = len; i < max_length + rec_width; ++i) printf("─");
        printf("┤\n");
    }

    if (it->get_child() != nullptr) dfs(it->get_child(), dep + 1);
    if (it->get_next() != nullptr) dfs(it->get_next(), dep);
}
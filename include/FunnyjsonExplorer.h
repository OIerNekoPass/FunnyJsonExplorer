// FunnyjsonExplorer.h
#ifndef FUNNYJSONEXPLORER_H
#define FUNNYJSONEXPLORER_H
#include <iostream>
#include <cstdlib>
#include <vector>
#include "Container.h"
#include "cJSON.h"

class FunnyjsonExplorer{ // Abstract Factory
private:
    std::string node_icon, leaf_icon;
public:
    Container *json_tree;

    bool _load(std::string file);
    Container* json_to_container(cJSON *parser);
    void set_icon(std::string ni, std::string li);

    virtual void CreateStyle() = 0;
};

class TreeStyleFactory : public FunnyjsonExplorer{
private:
    std::vector<bool> stack;
public:
    void CreateStyle() override;
    void dfs(Container *it);
};

class RectangleStyleFactory : public FunnyjsonExplorer{
private:
    int max_length, json_size, output_count;
public:
    void CreateStyle() override;
    void get_rec_info(Container *it, int dep);
    void dfs(Container *it, int dep);
};

#endif
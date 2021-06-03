#pragma once

#include <fstream>
#include <iostream>
#include <memory>
#include <stdlib.h>
#include "../third_party/json.hpp"

struct cords_t
{
public:
    cords_t(int x, int y);
    cords_t(cords_t cords,int x_add, int y_add);
    cords_t();
    int x_, y_;
};

struct color_t
{
public:
    color_t(int r, int g, int b, int a);
    color_t();
    int r_, g_, b_, a_;
};



enum CELL{
    ALIVE,
    DEAD
};
enum ENV{
    FIRE,
    WATER,
    SAND
};
std::map<std::string,CELL> static cell_enum_map{
    {"alive",CELL::ALIVE},
    {"dead",CELL::DEAD}
};
std::map<std::string,ENV> static env_enum_map{
    {"fire",ENV::FIRE},
    {"sand",ENV::SAND},
    {"water",ENV::WATER}
};

class config_t
{
public:
    int height_, width_, cell_size_, map_size_;
    bool load_map_from_file;
    std::string map_file_path;
    std::map<CELL, color_t> state_map_;
    std::map<ENV, color_t> env_map_;
};
class utils
{
public:
    std::shared_ptr<config_t> static load_config_f(std::string path)
    {
        nlohmann::json config_json;
        std::ifstream is(path); // open file
        config_json = nlohmann::json::parse(is);
        is.close();
        if (verify_config_f(config_json))
        {
            config_t *config = new config_t;
            config->map_file_path = config_json["map_file_path"];
            config->load_map_from_file = config_json["load_map_from_file"];
            config->height_ = config_json["height"];
            config->width_ = config_json["width"];
            config->cell_size_ = config_json["cell_size"];
            config->map_size_ = config_json["map_size"];

            printf("config: %d  %d %d %d",config->height_,config->width_,config->cell_size_,config->map_size_);
            for (auto& el : config_json["state_map"].items())
            {
                config->state_map_.emplace(cell_enum_map.at(el.key().c_str()), color_t(
                                                  el.value()["r"],
                                                  el.value()["g"],
                                                  el.value()["b"],
                                                  el.value()["a"]));
            }

            for (auto& el : config_json["env_map"].items())
            {
                config->env_map_.emplace(env_enum_map.at(el.key().c_str()), color_t(
                                                  el.value()["r"],
                                                  el.value()["g"],
                                                  el.value()["b"],
                                                  el.value()["a"]));
            
            }

            return std::shared_ptr<config_t>(config);
        }
        else
        {
            return nullptr;
        }
    };

private:
    bool static verify_config_f(nlohmann::json config)
    {
        return true;
    };
};
#pragma once

#include <fstream>
#include <iostream>
#include <memory>

#include "../third_party/json.hpp"

struct cords_t
{
public:
    cords_t(int x, int y);
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

class config_t
{
public:
    int height_, width_, cell_size_, map_size_;
    std::map<int, color_t> state_map_;
    std::map<int, color_t> env_map_;
};

class utills
{
public:
    std::shared_ptr<config_t> static load_config_f(std::string path)
    {
        nlohmann::json config_json;
        std::ifstream is(path); // open file
        config_json = nlohmann::json::parse(is);
        if (verify_config_f(config_json))
        {
            config_t *config = new config_t;
            config->height_ = config_json["height"];
            config->width_ = config_json["width"];
            config->cell_size_ = config_json["cell_size"];
            config->map_size_ = config_json["map_size"];

            printf("config: %d  %d %d %d",config->height_,config->width_,config->cell_size_,config->map_size_);

            for (unsigned i = 0; i < config_json["state_map"].size(); i++)
            {
                config->state_map_.emplace(i, color_t(
                                                  config_json["state_map"].at(i)["r"],
                                                  config_json["state_map"].at(i)["g"],
                                                  config_json["state_map"].at(i)["b"],
                                                  config_json["state_map"].at(i)["a"]));
            }

            for (unsigned i = 0; i < config_json.at("env_map").size(); i++)
            {
                config->env_map_.emplace(i, color_t(
                                                config_json["env_map"].at(i)["r"],
                                                config_json["env_map"].at(i)["g"],
                                                config_json["env_map"].at(i)["b"],
                                                config_json["env_map"].at(i)["a"]));
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
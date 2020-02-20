#pragma once

#include <iostream>
#include <memory>

#include "../third_party/json.hpp"


struct cords_t
{
public:
    int x_, y_;
};

struct color_t
{
    int r, g, b, a;
};

class config_t
{
public:
    int cell_size_, map_size_;
    std::map<int, color_t> state_map;
    std::map<int, color_t> env_map;
};


class utills
{
public:
    std::shared_ptr<config_t> static load_config_f(std::string path){};

private:
    bool verify_config_f(nlohmann::json config);
};
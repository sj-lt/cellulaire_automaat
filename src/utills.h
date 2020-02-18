#pragma once

#include <memory>

#include "../third_party/json.hpp"

struct cords_t
{
public:
    int x_, y_;
};

struct color_t
{
    int r,g,b,a;
};

struct config_t
{
public:
    int cell_size_, map_size_;
    std::map<int,color_t> state_map;
};

class utills
{
    public:
    std::shared_ptr<config_t> load_config_f();
    private:
    bool verify_config_f(nlohmann::json config);
};
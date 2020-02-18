#pragma once

#include <memory>

#include "../third_party/json.hpp"
#include "cell.h"
#include "environment.h"

typedef std::map<int, color_t> state_map_container;
typedef std::vector<cell_t> cell_container;
typedef std::vector<environment_t> env_container;
typedef std::shared_ptr<config_t> config_pointer;

struct cords_t
{
public:
    int x_, y_;
};

struct color_t
{
    int r, g, b, a;
};

struct config_t
{
public:
    int cell_size_, map_size_;
    state_map_container state_map;
};

class utills
{
public:
    std::shared_ptr<config_t> load_config_f();

private:
    bool verify_config_f(nlohmann::json config);
};
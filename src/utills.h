#pragma once

#include "../third_party/json.hpp"

struct cords_t
{
public:
    int x_, y_;
};

class utills
{
    public:
    nlohmann::json load_config_f();
    private:
    bool verify_config_f(nlohmann::json config);
};
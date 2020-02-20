#pragma once
#include <SDL2/SDL.h>

#include "map.h"
class world_t
{
public:
    world_t(std::shared_ptr<config_t> config);
    world_t();

    void render_map();
    void create_map();
private:
    std::shared_ptr<config_t> config_;
    map_t map_;
};
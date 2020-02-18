#pragma once
#include <SDL2/SDL.h>

#include "map.h"
class world_t
{
public:
    world_t(config_pointer config);
    world_t();

    void render_map();
    void create_map();
private:
    config_pointer config_;
    map_t map_;
};
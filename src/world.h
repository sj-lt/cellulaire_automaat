#pragma once
#include <SDL2/SDL.h>

#include "map.h"
class world_t
{
public:
    void render_map();

private:
    map_t map_;
};
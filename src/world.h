#pragma once
#include <SDL2/SDL.h>

#include "map.h"
class world_t
{
public:
    world_t(std::shared_ptr<config_t> config);
    world_t();

    void render_map_f(SDL_Renderer * renderer);
    void create_map_f();
private:
    std::shared_ptr<config_t> config_;
    // std::shared_ptr<map_t> map_;
    map_t map_;
};
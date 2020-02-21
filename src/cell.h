#pragma once

#include "render_object.h"

class cell_t : public render_object_t
{

public:

    void calculate_cell_f(const std::vector<cell_t>& cell_map_);
    void draw_f(SDL_Renderer * renderer);
    cell_t(std::shared_ptr<config_t> config) : render_object_t(config){};
private:
    int state_=0;
};
#pragma once

#include "render_object.h"

class cell_t : public render_object_t
{
public:
    void calculate_cell(const cell_container& cell_map_);
    void draw(SDL_Renderer * renderer);
    cell_t(config_pointer config) : render_object_t(config){};
private:
    int state_;
};
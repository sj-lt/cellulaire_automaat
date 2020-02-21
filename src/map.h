#pragma once

#include <vector>

#include "cell.h"
#include "environment.h"

class map_t
{
public:
    map_t(std::shared_ptr<config_t> config);
    map_t();

    // std::shared_ptr<map_t> generate_map_f();
    void generate_map_f();
    void render_map_f(SDL_Renderer * renderer);

    void calculate_cells_f();
    void print_config_f();

private:
    void generate_env_f();
    void generate_cells_f();
    void render_env_f(SDL_Renderer * renderer);
    void render_cells_f(SDL_Renderer * renderer);

    std::shared_ptr<config_t> config_;
    std::map<cords_t,environment_t> env_map_;
    std::map<cords_t,cell_t> cell_map_;
};
#include "map.h"

map_t::map_t(std::shared_ptr<config_t> config)
{
    config_ = config;
};
map_t::map_t(){};

void map_t::generate_map_f(){};
void map_t::generate_cells_f(){};
void map_t::calculate_cells_f(){};
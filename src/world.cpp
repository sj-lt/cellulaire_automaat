#include "world.h"

world_t::world_t(std::shared_ptr<config_t> config)
{
    config_ = config;
};
world_t::world_t(){};
void world_t::render_map(){};
void world_t::create_map(){};

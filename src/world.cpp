#include "world.h"

world_t::world_t(std::shared_ptr<config_t> config)
{
    config_ = config;
};
world_t::world_t(){};

void world_t::render_map_f(SDL_Renderer * renderer){
    map_.render_map_f(renderer);

};
void world_t::create_map_f(){
    std::cout << "start create map" << std::endl;
    map_ = map_t(config_);
    map_.generate_map_f();
    // map_->print_config_f();
    std::cout << "finish create map" << std::endl;
};

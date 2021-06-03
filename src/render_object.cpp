#include "render_object.h"

render_object_t::render_object_t(std::shared_ptr<config_t> config, cords_t coordinates)
{
    config_ = config;
    coordinates_ = coordinates;
};
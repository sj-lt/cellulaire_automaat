#pragma once

#include "world.h"

class game_t
{
public:
    game_t(config_pointer config);
    game_t();


private:
    world_t world_;
    config_pointer config_;

};

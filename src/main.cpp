#include "game.h"
/*
*TODO:
*- Create main create_game_f();
*- Create default config + some menu to edit configs
*-  GAME:
*-      void create_world_f();
*-      
*-  WORLD:
*-      void render_map();
*-      void create_map();
*-  MAP:
*-      void generate_map_f();
*-      void calculate_cells_f();
*-      void generate_cells_f();
*/
int main(int argc, char **argv)
{
    std::shared_ptr<config_t> config;
    //Read config
    if (argc > 1)
    {
        config = utills::load_config_f(argv[1]);
    }
    else
    {
        return 1; // try to load default config 
    }

    game_t game(config);
    game.init_game_f();
    game.start_game_f();
    return 0;
}
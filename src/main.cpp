#include "game.h"
/*
*TODO:
*- some menu to edit configs
*-  CELL:
*-      calculate cell 
*-  GAME:
*-      interupts function / input proccesing 
*-  MAP:
*-      void calculate_cells_f();
*-      make map as sharedptr as in hardware!!!!!!!!!!!!
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
        return -1; // try to load default config 
    }
    if(config == nullptr)
    {
        return -1;
    }

    game_t game(config);
    game.init_game_f();
    game.start_game_f();
    return 0;
}
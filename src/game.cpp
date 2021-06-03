#include "game.h"

game_t::game_t(std::shared_ptr<config_t> config)
{
    config_ = config;
};
game_t::game_t(){

};

void game_t::init_game_f()
{
    std::cout << "start init game" << std::endl;
    hardware_ = create_hardware_f();
    printf("config: %d  %d %d %d", config_->height_, config_->width_, config_->cell_size_, config_->map_size_);

    world_ = world_t(config_);
    std::cout << "finish init game" << std::endl;
};
void game_t::init_map_f()
{
    std::cout << "start init map" << std::endl;
    world_.create_map_f();
    std::cout << "finish init map" << std::endl;
};
void game_t::start_game_f()
{
    std::cout << "start start game" << std::endl;
    Uint32 frameStart;
    int frameTime;
    const int FPS = 15;
    const int frameDelay = 1000 / FPS;
    long time = 1;
    long step = 0;
    for (bool game_active = true; game_active; time++)
    {

        frameStart = SDL_GetTicks();
        SDL_Event event;
        event_enum evnt = NONE;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                evnt = QUIT;
                break;
            }
        }
        if (evnt != NONE)
        {
            game_active = false;
        }

        world_.render_map_f(hardware_->renderer);
        if (time % 10 == 0)
        {
            world_.calculate_cells_f();
            std::cout << step << std::endl;
            step++;
        }
        // if (world_.if_finish_f())
        // {
        //     game_active = false;
        // }
        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    std::cout << "finish start game" << std::endl;
};

std::shared_ptr<hardware_objects_t> game_t::create_hardware_f()
{
    return hardware_objects_t().init_hardware_subsystems(config_->width_, config_->height_, false);
};
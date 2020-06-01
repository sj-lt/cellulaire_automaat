#include "map.h"
#include <random>

map_t::map_t(std::shared_ptr<config_t> config)
{
    config_ = config;
};
map_t::map_t(){};

void map_t::print_config_f()
{
    printf("config: %d  %d %d %d", config_->height_, config_->width_, config_->cell_size_, config_->map_size_);
};

std::unique_ptr<map_t> map_t::generate_map_f()
{
    map_t *map = new map_t(config_);
    map->cell_map_ = generate_cells_f();
    map->env_map_ = generate_env_f();

    return std::unique_ptr<map_t>(map);
};

void map_t::render_map_f(SDL_Renderer *renderer)
{
    render_env_f(renderer);
    render_cells_f(renderer);
};

std::shared_ptr<std::map<cords_t, cell_t>> map_t::generate_cells_f()
{
    std::random_device rd;
    std::mt19937 eng(1);
    std::uniform_real_distribution<> distrReal(0, 1);



    std::cout << "start generate cells" << std::endl;
    std::map<cords_t, cell_t> *cell_map = new std::map<cords_t, cell_t>();
    unsigned int cells_width_n = (config_->width_ / config_->cell_size_);
    unsigned int cells_height_n = (config_->height_ / config_->cell_size_);
    for (unsigned int x = 0; x < cells_width_n; x++)
    {
        for (unsigned int y = 0; y < cells_height_n; y++)
        {
            cords_t cords(x, y);
            cell_t cell(config_, cords);
            if (distrReal(eng) > 0.2)
            {
                cell.state_ = CELL::DEAD;
                cell.next_state_ = CELL::DEAD;
            }
            cell_map->emplace(cords, cell);
        }
    }

    return std::shared_ptr<std::map<cords_t, cell_t>>(cell_map);
};

std::shared_ptr<std::map<cords_t, environment_t>> map_t::generate_env_f()
{
    //maybe return pointer
    std::cout << "start generate env" << std::endl;
    std::map<cords_t, environment_t> *env_map = new std::map<cords_t, environment_t>();

    unsigned int cells_width_n = (config_->width_ / config_->cell_size_);
    unsigned int cells_height_n = (config_->height_ / config_->cell_size_);
    for (unsigned int x = 0; x < cells_width_n; x++)
    {
        for (unsigned int y = 0; y < cells_height_n; y++)
        {
            cords_t cords(x, y);
            environment_t env(config_, cords);
            // if(x%5 == 0)
            // {
            //     env.state_ = ENV::FIRE; //FIRE
            // }
            // else
            // {
            //     env.state_ = ENV::WATER; //WATER
            // }
            env_map->emplace(cords, env);
        }
    }
    return std::shared_ptr<std::map<cords_t, environment_t>>(env_map);
};

void map_t::render_cells_f(SDL_Renderer *renderer)
{
    //maybe return pointer
    unsigned int cells_width_n = (config_->width_ / config_->cell_size_); //calculate in config??
    unsigned int cells_height_n = (config_->height_ / config_->cell_size_);

    for (unsigned int x = 0; x < cells_width_n; x++)
    {
        for (unsigned int y = 0; y < cells_height_n; y++)
        {
            cell_map_->at(cords_t(x, y)).draw_f(renderer);
        }
    }
};

void map_t::render_env_f(SDL_Renderer *renderer)
{
    //maybe return pointer
    unsigned int cells_width_n = (config_->width_ / config_->cell_size_);
    unsigned int cells_height_n = (config_->height_ / config_->cell_size_);

    for (unsigned int x = 0; x < cells_width_n; x++)
    {
        for (unsigned int y = 0; y < cells_height_n; y++)
        {
            env_map_->at(cords_t(x, y)).draw_f(renderer);
        }
    }
};

void map_t::calculate_cells_f()
{
    unsigned int cells_width_n = (config_->width_ / config_->cell_size_);
    unsigned int cells_height_n = (config_->height_ / config_->cell_size_);
    for (unsigned int x = 0; x < cells_width_n; x++)
    {
        for (unsigned int y = 0; y < cells_height_n; y++)
        {
            cell_map_->at(cords_t(x, y)).calculate_cell_f(this);
        }
    }
    for (unsigned int x = 0; x < cells_width_n; x++)
    {
        for (unsigned int y = 0; y < cells_height_n; y++)
        {
            cell_map_->at(cords_t(x, y)).next_day_f();
        }
    }
};


#include "map.h"
#include <random>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
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
std::unique_ptr<map_t> map_t::load_map_f()
{
    map_t *map = new map_t(config_);
    map->cell_map_ = load_cells_f();
    map->env_map_ = generate_env_f();

    return std::unique_ptr<map_t>(map);
};

void map_t::render_map_f(SDL_Renderer *renderer)
{
    render_env_f(renderer);
    render_cells_f(renderer);
};

std::shared_ptr<std::map<cords_t, cell_t>> map_t::load_cells_f()
{

    std::cout << "start load cells" << std::endl;
    std::map<cords_t, cell_t> *cell_map = new std::map<cords_t, cell_t>();
    unsigned int cells_width_n = (config_->width_ / config_->cell_size_);
    unsigned int cells_height_n = (config_->height_ / config_->cell_size_);

    std::ifstream is(config_->map_file_path);
    std::istringstream iss(std::string((std::istreambuf_iterator<char>(is)),
    std::istreambuf_iterator<char>()));
    auto rows = std::vector<std::string>((std::istream_iterator<std::string>(iss)),
                                     std::istream_iterator<std::string>());
    // if (rows.size() != cells_height_n)
    // {
    //     throw std::invalid_argument("rows dont match with size");
    // }
    // for (size_t i = 0; i < cells_height_n; i++)
    // {
    //     if (rows.at(i).size() != cells_width_n)
    //     {
    //         throw std::invalid_argument("rows dont match with size");
    //     }
    // }

    for (unsigned int x = 0; x < cells_width_n; x++)
    {
        for (unsigned int y = 0; y < cells_height_n; y++)
        {
            cords_t cords(x, y);
            cell_t cell(config_, cords);
            CELL state;
            switch (rows.at(y).at(x))
            {
            case '#':
                state = CELL::ALIVE;
                break;
            case '.':
                state = CELL::DEAD;
                break;
            default:
                state = CELL::DEAD;
                break;
            }

            cell.state_ = state;
            cell.next_state_ = state;
            cell_map->emplace(cords, cell);
        }
    }

    return std::shared_ptr<std::map<cords_t, cell_t>>(cell_map);
};

std::shared_ptr<std::map<cords_t, cell_t>> map_t::generate_cells_f()
{
    std::random_device rd;
    std::mt19937 eng(rd());
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
    // finish = if_same_f();
    for (unsigned int x = 0; x < cells_width_n; x++)
    {
        for (unsigned int y = 0; y < cells_height_n; y++)
        {
            cell_map_->at(cords_t(x, y)).next_day_f();
        }
    }
};

bool map_t::if_same_f()
{
    unsigned int cells_width_n = (config_->width_ / config_->cell_size_);
    unsigned int cells_height_n = (config_->height_ / config_->cell_size_);
    for (unsigned int x = 0; x < cells_width_n; x++)
    {
        for (unsigned int y = 0; y < cells_height_n; y++)
        {
            if (cell_map_->at(cords_t(x, y)).state_ != cell_map_->at(cords_t(x, y)).next_state_)
            {
                same_counter = 1;
                return false;
            }
        }
    }
    same_counter += 1;
    if (same_counter > 1)
    {
        return true;
    }
    return false;
}

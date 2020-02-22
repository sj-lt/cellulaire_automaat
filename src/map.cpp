#include "map.h"

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

std::unique_ptr<std::map<cords_t, cell_t>> map_t::generate_cells_f()
{
    std::cout << "start generate cells" << std::endl;
    std::map<cords_t, cell_t> *cell_map = new std::map<cords_t, cell_t>();
    unsigned int cells_width_n = (config_->width_ / config_->cell_size_);
    unsigned int cells_height_n = (config_->height_ / config_->cell_size_);
    for (unsigned int x = 0; x < cells_width_n; x++)
    {
        for (unsigned int y = 0; y < cells_height_n; y++)
        {
            cords_t cords(x, y);
            cell_map->emplace(cords, cell_t(config_, cords));
        }
    }

    return std::unique_ptr<std::map<cords_t, cell_t>>(cell_map);
};

std::unique_ptr<std::map<cords_t, environment_t>> map_t::generate_env_f()
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
            if(x%5 == 0)
            {
                env.state_ = 1; //FIRE
            }
            else
            {
                env.state_ = 0; //WATER
            }
            env_map->emplace(cords, env);
        }
    }
    return std::unique_ptr<std::map<cords_t, environment_t>>(env_map);
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
};

inline bool operator<(const cords_t &l, const cords_t &r)
{
    return (l.x_ < r.x_ || (l.x_ == r.x_ && l.y_ < r.y_));
}
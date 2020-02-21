#include "map.h"

map_t::map_t(std::shared_ptr<config_t> config)
{
    config_ = config;
};
map_t::map_t(){};

void map_t::print_config_f()
{
    printf("config: %d  %d %d %d",config_->height_,config_->width_,config_->cell_size_,config_->map_size_);
};

void map_t::generate_map_f()
{
    std::cout << "start generate map" << std::endl;
    printf("config: %d  %d %d %d",config_->height_,config_->width_,config_->cell_size_,config_->map_size_);

    generate_env_f();
    generate_cells_f();

    std::cout << "finish generate map" << std::endl;
    // return std::shared_ptr<map_t>(this);
};
void map_t::generate_cells_f()
{
    //maybe return pointer
    std::cout << "start generate cells" << std::endl;

    unsigned int cells_width_n = (config_->width_ / config_->cell_size_);
    unsigned int cells_height_n = (config_->height_ / config_->cell_size_);
    for (unsigned int x = 0; x < cells_width_n; x++)
    {
        for (unsigned int y = 0; y < cells_height_n; y++)
        {
            cell_map_.emplace(cords_t(x, y), cell_t(config_));
        }
    }
};
void map_t::generate_env_f()
{
    //maybe return pointer
    //maybe return pointer
    std::cout << "start generate env" << std::endl;


    unsigned int cells_width_n = (config_->width_ / config_->cell_size_);
    unsigned int cells_height_n = (config_->height_ / config_->cell_size_);
    for (unsigned int x = 0; x < cells_width_n; x++)
    {
        for (unsigned int y = 0; y < cells_height_n; y++)
        {
            env_map_.emplace(cords_t(x, y), environment_t(config_));
        }
    }
};

void map_t::render_map_f(SDL_Renderer *renderer)
{
    std::cout << "start render map in map_t" << std::endl;
    render_env_f(renderer);
    render_cells_f(renderer);
    std::cout << "finish render map in map_t" << std::endl;
};
void map_t::render_cells_f(SDL_Renderer *renderer)
{
    //maybe return pointer
    unsigned int cells_width_n = (config_->width_ / config_->cell_size_); //calculate in config??
    printf("config: %d  %d %d %d",config_->height_,config_->width_,config_->cell_size_,config_->map_size_);

    unsigned int cells_height_n = (config_->height_ / config_->cell_size_);
    for (unsigned int x = 0; x < cells_width_n; x++)
    {
        for (unsigned int y = 0; y < cells_height_n; y++)
        {
            cell_map_.at(cords_t(x, y)).draw_f(renderer);
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
            env_map_.at(cords_t(x, y)).draw_f(renderer);
        }
    }
};

void map_t::calculate_cells_f(){};

inline bool operator<(const cords_t &l, const cords_t &r)
{
    return (l.x_ < r.x_ || (l.x_ == r.x_ && l.y_ < r.y_));
}
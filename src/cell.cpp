#include "cell.h"

void cell_t::draw_f(SDL_Renderer *renderer)
{
    SDL_Rect rect = {((cordinates_.x_) * (config_->cell_size_)),
                     ((cordinates_.y_) * (config_->cell_size_)),
                     config_->cell_size_, config_->cell_size_};

    SDL_SetRenderDrawColor(renderer,
                           config_->state_map_.at(state_).r_,
                           config_->state_map_.at(state_).g_,
                           config_->state_map_.at(state_).b_,
                           config_->state_map_.at(state_).a_);

    SDL_RenderFillRect(renderer, &rect);
};
void cell_t::calculate_cell_f(const map_t *map)
{
//REMOVE FROM MOVES INCORRECT ONES;
std::vector<std::pair<int,int>> possible_moves = pick_possible_moves_f(map); //TODO pass as pointer

    // IF NEIGHTBOURS ARE FIRE DIE  //TODO MAKE WITH COUNT NEIGHBOURS WITH TEMPLATES
    if (map->env_map_->at(cordinates_).state_ == 1 || map->env_map_->at(cords_t(cordinates_, 1, 0)).state_ == 1 || map->env_map_->at(cords_t(cordinates_, -1, 0)).state_ == 1 || map->env_map_->at(cords_t(cordinates_, 0, 1)).state_ == 1 || map->env_map_->at(cords_t(cordinates_, 0, -1)).state_ == 1)
    {
        next_state_ = 1;
    }
    // IF NEIGHTBOURS ARE WATER CREATE //TODO MAKE WITH COUNT NEIGHBOURS WITH TEMPLATES
    else if (map->env_map_->at(cordinates_).state_ == 0 || map->env_map_->at(cords_t(cordinates_, 1, 0)).state_ == 0 || map->env_map_->at(cords_t(cordinates_, -1, 0)).state_ == 0 || map->env_map_->at(cords_t(cordinates_, 0, 1)).state_ == 0 || map->env_map_->at(cords_t(cordinates_, 0, -1)).state_ == 0)
    {

        if (count_neighbours_f(map, 0,possible_moves) > 3)
        {
            next_state_ = 1;
        }
        else
        {
            next_state_ = 0;
        }
    }
};
void cell_t::next_day_f()
{
    state_ = next_state_;
};
//TODO MAKE TEMPLATE FOR MAPS !!!!!!!
int cell_t::count_neighbours_f(const map_t *map, int state_to_count,std::vector<std::pair<int,int>> moves)
{
    int counter = 0;
    for (unsigned int i = 0; i < moves.size(); i++)
    {
        if (map->cell_map_->at(cords_t(cordinates_, moves.at(i).first, moves.at(i).second)).state_ == state_to_count)
        {
            counter++;
        }
    }
    return counter;
}
std::vector<std::pair<int,int>> cell_t::pick_possible_moves_f(const map_t *map)
{
    std::vector<std::pair<int,int>> moves;
    for (unsigned int i = 0; i < moves_.size(); i++)
    {   //find moves within the map
        if (map->cell_map_->find(cords_t(cordinates_, moves_.at(i).first, moves_.at(i).second)) != map->cell_map_->end())
        {
            moves.push_back(moves_.at(i));
        }
    }
    return moves;
}
cell_t::cell_t(std::shared_ptr<config_t> config, cords_t cordinates) : render_object_t(config, cordinates) {}
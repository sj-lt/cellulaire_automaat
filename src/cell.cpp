#include "cell.h"

void cell_t::draw_f(SDL_Renderer *renderer)
{
    SDL_Rect rect = {((coordinates_.x_) * (config_->cell_size_)),
                     ((coordinates_.y_) * (config_->cell_size_)),
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
    std::vector<std::pair<int, int>> possible_moves = pick_possible_moves_f(map); //TODO pass as pointer

    int dead_neighbors = count_neighbour_f(map->cell_map_, CELL::DEAD, possible_moves);
    int alive_neighbors = count_neighbour_f(map->cell_map_, CELL::ALIVE, possible_moves);
    if(state_ == CELL::DEAD && alive_neighbors == 3)
    {
        next_state_ = CELL::ALIVE;
        return;
    }
    if(state_ == CELL::ALIVE && (alive_neighbors == 2 || alive_neighbors == 3))
    {
        next_state_ = CELL::ALIVE;
        return;
    }
    next_state_ = CELL::DEAD;
};

void cell_t::next_day_f()
{
    state_ = next_state_;
};

template <class map_T, class enum_T>
int cell_t::count_neighbour_f(const map_T map, enum_T state_to_count, std::vector<std::pair<int, int>> moves)
{
    int counter = 0;
    for (unsigned int i = 0; i < moves.size(); i++)
    {
        if (map->at(cords_t(coordinates_, moves.at(i).first, moves.at(i).second)).state_ == state_to_count)
        {
            counter++;
        }
    }
    return counter;
}

//TODO MAKE TEMPLATE FOR MAPS !!!!!!!
std::vector<std::pair<int, int>> cell_t::pick_possible_moves_f(const map_t *map)
{
    std::vector<std::pair<int, int>> moves;
    for (unsigned int i = 0; i < moves_.size(); i++)
    { //IF MOVE WITHIN MAP
        if (map->cell_map_->find(cords_t(coordinates_, moves_.at(i).first, moves_.at(i).second)) != map->cell_map_->end())
        {
            moves.push_back(moves_.at(i));
        }
    }
    return moves;
}
cell_t::cell_t(std::shared_ptr<config_t> config, cords_t coordinates) : render_object_t(config, coordinates) {}
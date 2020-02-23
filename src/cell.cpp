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
    std::vector<std::pair<int, int>> possible_moves = pick_possible_moves_f(map); //TODO pass as pointer

                                            // if (count_neighbours_f(map->env_map_,ENV::FIRE,possible_moves)>=1)
                                            // {
                                            //     next_state_ = CELL::DEAD;;
                                            // }

                                            // else if (count_neighbours_f(map->env_map_,ENV::WATER,possible_moves)>=1)
                                            // {

                                            //     if (count_neighbours_f(map->cell_map_, CELL::ALIVE, possible_moves) > 3)
                                            //     {
                                            //         next_state_ = CELL::DEAD;
                                            //     }
                                            //     else
                                            //     {
                                            //         next_state_ = CELL::ALIVE;
                                            //     }
                                            // }

        if (count_neighbours_f(map->cell_map_, CELL::ALIVE, possible_moves) > 3)
        {
            next_state_ = CELL::DEAD;
        }
        else
        {
            next_state_ = CELL::ALIVE;
        }

    //TODO add if one cell naighbour then make alive if more than 3 die
};

void cell_t::next_day_f()
{
    state_ = next_state_;
};

template <class map_T,class enum_T>
int cell_t::count_neighbours_f(const map_T map, enum_T state_to_count, std::vector<std::pair<int, int>> moves)
{
    int counter = 0;
    for (unsigned int i = 0; i < moves.size(); i++)
    {
        if (map-> at(cords_t(cordinates_, moves.at(i).first, moves.at(i).second)).state_ == state_to_count)
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
        if (map->cell_map_->find(cords_t(cordinates_, moves_.at(i).first, moves_.at(i).second)) != map->cell_map_->end())
        {
            moves.push_back(moves_.at(i));
        }
    }
    return moves;
}
cell_t::cell_t(std::shared_ptr<config_t> config, cords_t cordinates) : render_object_t(config, cordinates) {}

#include "cell.h"

void cell_t::draw_f(SDL_Renderer *renderer)
{
    SDL_Rect rect = {((cordinates_.x_) * (config_->cell_size_)),
                     ((cordinates_.y_) * (config_->cell_size_)),
                     config_->cell_size_, config_->cell_size_};

    SDL_SetRenderDrawColor(renderer,
                           config_->state_map.at(state_).r,
                           config_->state_map.at(state_).g,
                           config_->state_map.at(state_).b,
                           config_->state_map.at(state_).a);

    SDL_RenderFillRect(renderer, &rect);
};
void cell_t::calculate_cell_f(const std::vector<cell_t>& cell_map_){
    //TODO
};

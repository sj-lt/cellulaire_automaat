#include "environment.h"
void environment_t::draw_f(SDL_Renderer *renderer)
{
    SDL_Rect rect = {((cordinates_.x_) * (config_->cell_size_)),
                     ((cordinates_.y_) * (config_->cell_size_)),
                     config_->cell_size_, config_->cell_size_};

    SDL_SetRenderDrawColor(renderer,
                           config_->env_map_.at(state_).r_,
                           config_->env_map_.at(state_).g_,
                           config_->env_map_.at(state_).b_,
                           config_->env_map_.at(state_).a_);

    SDL_RenderFillRect(renderer, &rect);
};
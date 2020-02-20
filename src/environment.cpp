#include "environment.h"
void environment_t::draw_f(SDL_Renderer *renderer)
{
    SDL_Rect rect = {((cordinates_.x_) * (config_->cell_size_)),
                     ((cordinates_.y_) * (config_->cell_size_)),
                     config_->cell_size_, config_->cell_size_};

    SDL_SetRenderDrawColor(renderer,
                           config_->env_map.at(type_).r,
                           config_->env_map.at(type_).g,
                           config_->env_map.at(type_).b,
                           config_->env_map.at(type_).a);

    SDL_RenderFillRect(renderer, &rect);
};
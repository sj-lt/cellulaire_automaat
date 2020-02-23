#pragma once

#include "render_object.h"
#include "map.h"

class map_t; //FORWARD DECLARATION

class cell_t : public render_object_t
{

public:
    void calculate_cell_f(const map_t *map);
    void draw_f(SDL_Renderer *renderer);
    void next_day_f();

    cell_t(std::shared_ptr<config_t> config, cords_t cordinates);
    CELL state_ = CELL::ALIVE;
    CELL next_state_ = CELL::ALIVE;
private:
    template <class map_T,class enum_T>
    int count_neighbours_f(const map_T map, enum_T state_to_count,std::vector<std::pair<int,int>> moves);
    std::vector<std::pair<int,int>> pick_possible_moves_f(const map_t *map);
    void life_rules_f(const map_t *map);

    const std::array<std::pair<int,int>,4> moves_ = {std::make_pair(1,0),{0,1},{-1,0},{0,-1}}; 
};
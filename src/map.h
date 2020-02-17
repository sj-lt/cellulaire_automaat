#pragma once

#include <vector>

#include "cell.h"
#include "environment.h"

class map_t
{
public:
    std::vector<environment_t> main_map_;
    std::vector<cell_t> cell_map_;

    void generate_map_f();
    void generate_cells_f();
    void calculate_cells_f();
};
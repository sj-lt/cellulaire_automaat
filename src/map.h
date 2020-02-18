#pragma once

#include <vector>

#include "cell.h"
#include "environment.h"

class map_t
{
public:
    map_t(config_pointer config);
    map_t();

    void generate_map_f();

    void calculate_cells_f();

private:
    void generate_cells_f();

    config_pointer config_;
    env_container main_map_;
    cell_container cell_map_;
};
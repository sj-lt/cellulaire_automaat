#pragma once

#include <vector>

#include "cell.h"
#include "environment.h"

class map_t
{
public:
    map_t(std::shared_ptr<config_t> config);
    map_t();

    void generate_map_f();

    void calculate_cells_f();

private:
    void generate_cells_f();

    std::shared_ptr<config_t> config_;
    std::vector<environment_t> main_map_;
    std::vector<cell_t> cell_map_;
};
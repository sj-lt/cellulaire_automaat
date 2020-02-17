#pragma once

#include "render_object.h"

class cell_t : public render_object_t
{
public:
    void calculate_cell(const std::vector<cell_t> &cell_map_);

};
#pragma once

#include <vector>

class World
{
public:
    World(int32_t units_per_block);

    size_t size_x() const;
    size_t size_y() const;
    int32_t units_per_block() const;

    int32_t GetBlock(int32_t x, int32_t y) const;

private:
    size_t size_x_;
    size_t size_y_;
    int32_t units_per_block_;

    std::vector<int32_t> world_;
};


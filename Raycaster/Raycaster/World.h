#pragma once

#include <vector>

class World
{
public:
    World();

    size_t GetSizeX() const;
    size_t GetSizeY() const;

    int32_t GetSquare(int32_t x, int32_t y) const;

private:
    size_t size_x_;
    size_t size_y_;

    std::vector<int32_t> world_;
};


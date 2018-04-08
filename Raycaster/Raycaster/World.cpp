#include "World.h"

World::World(int32_t units_per_block)
    :units_per_block_(units_per_block)
{
    size_x_ = 10;
    size_y_ = 10;

    world_ = {
        1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };
}

size_t World::size_x() const
{
    return size_x_;
}

size_t World::size_y() const
{
    return size_y_;
}

int32_t World::units_per_block() const
{
    return units_per_block_;
}

int32_t World::GetBlock(int32_t x, int32_t y) const
{
    if (x >= size_x() || y >= size_y())
        return 0;
    return world_[y* size_x_ + x];
}

bool World::IsInsideBlock(int32_t x, int32_t y) const
{
	const int32_t nbFullBlocksX = x / size_x();
	const int32_t nbFullBlocksY = x / size_y();

	return GetBlock(nbFullBlocksX, nbFullBlocksY);
}

bool World::IsInside(int32_t x, int32_t y) const
{
    const int32_t nbFullBlocksX = x / size_x();
    const int32_t nbFullBlocksY = x / size_y();

    return nbFullBlocksX < size_x() && nbFullBlocksY < size_y();
}

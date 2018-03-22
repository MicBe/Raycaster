#include "Framebuffer.h"

#include <algorithm>

Framebuffer::Framebuffer(uint32_t width, uint32_t height)
    : buffer_size_(width * height),
    buffer_(new uint32_t[buffer_size_]),
    width_(width),
    height_(height)
{
    Fill(0);
}

Framebuffer::~Framebuffer()
{
    delete[] buffer_;
}

const uint32_t* const Framebuffer::Get() const
{
    return buffer_;
}

uint32_t Framebuffer::width() const
{
    return width_;
}

uint32_t Framebuffer::height() const
{
    return height_;
}

void Framebuffer::Fill(uint32_t rgba)
{
    std::fill(buffer_, buffer_ + buffer_size_, rgba);
}

void Framebuffer::DrawHorizontalLine(uint32_t y, uint32_t rgba)
{
    DrawHorizontalLine(y, 0, width(), rgba);
}

void Framebuffer::DrawHorizontalLine(uint32_t y, uint32_t start_pos, uint32_t end_pos, uint32_t rgba)
{
    uint32_t* const line_start = buffer_ + (width() * y) + start_pos;
    std::fill(line_start, line_start + end_pos, rgba);
}

void Framebuffer::SetPixel(size_t x, size_t y, uint32_t rgba)
{
    buffer_[y * width() + x] = rgba;
}


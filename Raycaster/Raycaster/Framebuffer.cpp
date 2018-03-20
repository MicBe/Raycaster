#include "Framebuffer.h"

#include <algorithm>

Framebuffer::Framebuffer(uint32_t width, uint32_t height)
    : buffer_size_(width * height),
    buffer_(new uint32_t[buffer_size_]),
    width_(width),
    height_(height)
{
}

Framebuffer::~Framebuffer()
{
    delete[] buffer_;
}

const uint32_t* const Framebuffer::Get() const
{
    return buffer_;
}

uint32_t Framebuffer::GetWidth() const
{
    return width_;
}

uint32_t Framebuffer::GetHeight() const
{
    return height_;
}

void Framebuffer::Fill(uint32_t rgba)
{
    std::fill(buffer_, buffer_ + buffer_size_, rgba);
}

void Framebuffer::DrawHorizontalLine(uint32_t y, uint32_t rgba)
{
    uint32_t* const start_position = buffer_ + GetWidth() * y;
    std::fill(start_position, start_position + GetWidth(), rgba);
}

void Framebuffer::SetPixel(size_t x, size_t y, uint32_t rgba)
{
    buffer_[y * GetWidth() + x] = rgba;
}


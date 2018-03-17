#include "Framebuffer.h"

Framebuffer::Framebuffer(int32_t width, int32_t height, int32_t channels)
    :buffer_(width * height * channels),
    width_(width),
    height_(height),
    channels_(channels)
{
}

const uint8_t* const Framebuffer::Get() const
{
    return &buffer_[0];
}

int32_t Framebuffer::GetWidth() const
{
    return width_;
}

int32_t Framebuffer::GetHeight() const
{
    return height_;
}

void Framebuffer::SetPixel(size_t x, size_t y, uint8_t red, uint8_t green, uint8_t blue)
{
    size_t position = (y * GetWidth() * channels_) + (x * channels_);
    buffer_[position++] = red;
    buffer_[position++] = green;
    buffer_[position] = blue;
}


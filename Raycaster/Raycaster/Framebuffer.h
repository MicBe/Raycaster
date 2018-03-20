#pragma once

#include <cstdint>

class Framebuffer
{
public:
    Framebuffer(uint32_t width, uint32_t height);
    ~Framebuffer();

    const uint32_t* const Get() const;
    uint32_t GetWidth() const;
    uint32_t GetHeight() const;

    void Fill(uint32_t rgba);
    void DrawHorizontalLine(uint32_t y, uint32_t rgba);
    void DrawHorizontalLine(uint32_t y, uint32_t start_pos, uint32_t end_pos, uint32_t rgba);

    void SetPixel(size_t x, size_t y, uint32_t rgba);

private:
    size_t buffer_size_;
    uint32_t* buffer_;
    const uint32_t width_;
    const uint32_t height_;
};


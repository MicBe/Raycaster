#pragma once

#include <cstdint>
#include <vector>

class Framebuffer
{
public:
    Framebuffer(int32_t width, int32_t height, int32_t channels);

    const uint8_t* const Get() const;
    int32_t GetWidth() const;
    int32_t GetHeight() const;

    void SetPixel(size_t x, size_t y, uint8_t red, uint8_t green, uint8_t blue);

private:
    std::vector<uint8_t> buffer_;
    const int32_t width_;
    const int32_t height_;
    const int32_t channels_;
};


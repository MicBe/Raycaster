#pragma once

#include <glm/glm.hpp>

#include <utility>

class Camera
{
public:
    Camera(const glm::vec2& position, float orientation_deg,
           int32_t fov, int32_t height, float units_per_sec);

    void GoForward(int32_t time_elapsed);
    void GoBackward(int32_t time_elapsed);
    void RotateLeft(int32_t time_elapsed);
    void RotateRight(int32_t time_elapsed);

    const glm::vec2& position() const;
    float orientation_deg() const;
    int32_t fov() const;
    int32_t height();

private:
    std::pair<float, float> GetDeltaMove(int32_t time_elapsed) const;

	glm::vec2 position_;
    float orientation_deg_;
    int32_t fov_;
    int32_t height_;

    float movement_units_per_sec_;
    float rotation_angle_per_sec_;
};


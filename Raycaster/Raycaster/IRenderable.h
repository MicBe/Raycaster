#pragma once

class IRenderable
{
public:
    IRenderable() = default;
    IRenderable(const IRenderable&) = default;
    IRenderable(IRenderable&&) = default;
    IRenderable& operator=(const IRenderable&) = default;
    IRenderable& operator=(IRenderable&&) = default;
    virtual ~IRenderable() = default;

    virtual void Init() = 0;
    virtual void Render() = 0;
    virtual void Update() = 0;
};


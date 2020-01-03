#pragma once

class Actor
{
public:
    virtual void moveUp(const float& dt) = 0;
    virtual void moveDown(const float& dt) = 0;
    virtual void turnRight(const float& dt) = 0;
    virtual void turnLeft(const float& dt) = 0;
};
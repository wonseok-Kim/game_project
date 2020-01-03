#pragma once

#include "Actor.h"

class Command
{
public:
    virtual void execute(Actor& actor, const float& dt) = 0;
};

class UpCommand : public Command
{
public:
    void execute(Actor& actor, const float& dt) override
    {
        actor.moveUp(dt);
    }
};

class DownCommand : public Command
{
public:
    void execute(Actor& actor, const float& dt) override
    {
        actor.moveDown(dt);
    }
};

class RightCommand : public Command
{
public:
    void execute(Actor& actor, const float& dt) override
    {
        actor.turnRight(dt);
    }
};

class LeftCommand : public Command
{
public:
    void execute(Actor& actor, const float& dt) override
    {
        actor.turnLeft(dt);
    }
};
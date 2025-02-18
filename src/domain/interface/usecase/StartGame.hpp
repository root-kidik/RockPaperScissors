#pragma once

namespace rps::domain::interface::usecase
{

class StartGame
{
public:
    virtual ~StartGame() = default;

    virtual void start_game() = 0;
};

} // namespace rps::domain::interface::usecase

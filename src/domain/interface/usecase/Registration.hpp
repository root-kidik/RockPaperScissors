#pragma once

#include <string>

namespace rps::domain::interface::usecase
{

class Registration
{
public:
    virtual ~Registration() = default;

    virtual void registrate(std::string&& nickname) = 0;
};

} // namespace rps::domain::interface::usecase

#pragma once

#include <domain/entity/Mode.hpp>

namespace rps::domain::interface
{

class ModeManager
{
public:
    virtual ~ModeManager() = default;

    virtual void activate_mode(domain::entity::Mode mode) = 0;
};

} // namespace rps::domain::interface

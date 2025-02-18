#pragma once

#include <string>

namespace rps::domain::interface::usecase
{

class Searching
{
public:
    virtual ~Searching() = default;

    virtual void create_room(std::string room_name)     = 0;
    virtual void connect_to_room(std::string room_name) = 0;
};

} // namespace rps::domain::interface::usecase

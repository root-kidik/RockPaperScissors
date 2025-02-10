#pragma once

#include <QPixmap>

#include <unordered_map>

#include <RockPaperScissorsProtocol/entity/Card.hpp>

namespace rps::infrastructure::storage
{

class Pixmap
{
public:
    Pixmap();

    const QPixmap& get(rps::protocol::entity::Card card) const;

private:
    std::unordered_map<rps::protocol::entity::Card, QPixmap> m_pixmaps;
};

} // namespace rps::infrastructure::storage

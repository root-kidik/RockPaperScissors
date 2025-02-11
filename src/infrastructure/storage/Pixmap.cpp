#include <cassert>

#include <infrastructure/storage/Pixmap.hpp>

namespace
{
constexpr const char* kRockPngPath     = ":/assets/Rock.png";
constexpr const char* kPaperPngPath    = ":/assets/Paper.png";
constexpr const char* kScissorsPngPath = ":/assets/Scissors.png";
constexpr const char* kBackfacePngPath = ":/assets/Backface.png";
} // namespace

namespace rps::infrastructure::storage
{

Pixmap::Pixmap()
{
    using namespace rps::protocol::entity;

    m_pixmaps.emplace(Card::Rock, QPixmap{kRockPngPath});
    m_pixmaps.emplace(Card::Paper, QPixmap{kPaperPngPath});
    m_pixmaps.emplace(Card::Scissors, QPixmap{kScissorsPngPath});
    m_pixmaps.emplace(Card::Backface, QPixmap{kBackfacePngPath});
}

const QPixmap& Pixmap::get(rps::protocol::entity::Card card) const
{
    assert(m_pixmaps.find(card) != m_pixmaps.end() && "No pixmap for such card");
    return m_pixmaps.at(card);
}

} // namespace rps::infrastructure::storage
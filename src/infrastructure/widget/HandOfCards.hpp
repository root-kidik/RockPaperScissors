#pragma once

#include <QLayout>
#include <QPushButton>
#include <QResizeEvent>
#include <QWidget>

#include <cstdint>

#include <RockPaperScissorsProtocol/entity/Card.hpp>

namespace rps
{
namespace domain::model
{
class HandOfCards;
}

namespace infrastructure::storage
{
class Pixmap;
}
} // namespace rps

namespace rps::infrastructure::widget
{

class HandOfCards final : public QWidget
{
    Q_OBJECT

public:
    enum class Type : std::uint8_t
    {
        Horizontal,
        VerticalLeft,
        VerticalRight
    };

    HandOfCards(const storage::Pixmap& pixmap_storage, domain::model::HandOfCards& model, Type type, bool is_player_deck = false);

private:
    const storage::Pixmap&      m_pixmap_storage;
    domain::model::HandOfCards& m_model;

    std::array<QPushButton, protocol::entity::kMaxCardsPerPlayer> m_buttons;

    Type m_type;
    bool m_is_player_deck;
};

} // namespace rps::infrastructure::widget

#pragma once

#include <QLayout>
#include <QPushButton>
#include <QResizeEvent>
#include <QWidget>

#include <cstdint>

#include <RockPaperScissorsProtocol/entity/Card.hpp>

namespace rps::infrastructure::storage
{
class Pixmap;
}

namespace rps::infrastructure::widget
{

class HandOfCards : public QWidget
{
    Q_OBJECT

public:
    enum class Type
    {
        Horizontal,
        VerticalLeft,
        VerticalRight
    };

    HandOfCards(const storage::Pixmap& pixmap_storage, Type type);

    void add_card(protocol::entity::Card card);

private:
    const storage::Pixmap& m_pixmap_storage;

    std::uint8_t m_cards_count;

    std::array<QPushButton, protocol::entity::kMaxCardsPerPlayer> m_cards;

    Type m_type;
};

} // namespace rps::infrastructure::widget

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

    using CardIdx = std::uint8_t;

    HandOfCards(const storage::Pixmap& pixmap_storage, Type type, bool is_player_deck = false);

    void lock_card_selection(bool value);

    void add_card(protocol::entity::Card card);
    void replace_card(CardIdx idx, protocol::entity::Card card);
    void replace_by_value_to_backface(protocol::entity::Card card);

    void subscribe_on_card_selection(std::function<void(protocol::entity::Card, CardIdx)> callback);
    
    void select_card(protocol::entity::Card card);

private:
    const storage::Pixmap& m_pixmap_storage;

    struct Card
    {
        QPushButton            button;
        protocol::entity::Card type;
    };

    CardIdx m_cards_count;

    std::array<Card, protocol::entity::kMaxCardsPerPlayer> m_cards;

    Type m_type;
    bool m_is_player_deck;

    std::function<void(protocol::entity::Card, CardIdx)> m_on_card_selected;

    bool m_is_card_selection_locked;
};

} // namespace rps::infrastructure::widget

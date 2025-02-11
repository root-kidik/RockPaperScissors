#include <infrastructure/storage/Pixmap.hpp>
#include <infrastructure/widget/Room.hpp>

namespace rps::infrastructure::widget
{

Room::Room(domain::model::Room& model, const storage::Pixmap& pixmap_storage) :
m_model{model},
m_pixmap_storage{pixmap_storage},
m_player_hand{pixmap_storage, HandOfCards::Type::Horizontal},
m_east_hand{pixmap_storage, HandOfCards::Type::VerticalRight},
m_west_hand{pixmap_storage, HandOfCards::Type::VerticalLeft},
m_north_hand{pixmap_storage, HandOfCards::Type::Horizontal},
m_table{pixmap_storage, HandOfCards::Type::Horizontal}
{
    setLayout(&m_layout);

    m_layout.setAlignment(Qt::AlignCenter);

    m_player_hand.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_east_hand.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_west_hand.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_north_hand.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_table.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    using namespace rps::protocol::entity;

    m_player_hand.add_card(Card::Scissors);
    m_player_hand.add_card(Card::Paper);
    m_player_hand.add_card(Card::Rock);
    m_player_hand.add_card(Card::Scissors);
    m_player_hand.add_card(Card::Rock);
    m_player_hand.add_card(Card::Paper);

    m_north_hand.add_card(Card::Backface);
    m_north_hand.add_card(Card::Backface);
    m_north_hand.add_card(Card::Backface);
    m_north_hand.add_card(Card::Backface);
    m_north_hand.add_card(Card::Backface);
    m_north_hand.add_card(Card::Backface);

    m_west_hand.add_card(Card::Backface);
    m_west_hand.add_card(Card::Backface);
    m_west_hand.add_card(Card::Backface);
    m_west_hand.add_card(Card::Backface);
    m_west_hand.add_card(Card::Backface);
    m_west_hand.add_card(Card::Backface);

    m_east_hand.add_card(Card::Backface);
    m_east_hand.add_card(Card::Backface);
    m_east_hand.add_card(Card::Backface);
    m_east_hand.add_card(Card::Backface);
    m_east_hand.add_card(Card::Backface);
    m_east_hand.add_card(Card::Backface);

    m_table.add_card(Card::Scissors);
    m_table.add_card(Card::Paper);
    m_table.add_card(Card::Rock);
    m_table.add_card(Card::Scissors);
    m_table.add_card(Card::Rock);
    m_table.add_card(Card::Paper);

    m_layout.addWidget(&m_north_hand, 0, 1);
    m_layout.addWidget(&m_west_hand, 1, 0);
    m_layout.addWidget(&m_east_hand, 1, 2);
    m_layout.addWidget(&m_player_hand, 2, 1);

    m_layout.addWidget(&m_table, 1, 1);

    m_model.subsribe_on_new_player_addition(
        [this](std::string&& player_nickname)
        {
            // TODO(@rtkid): handle
        });
}

} // namespace rps::infrastructure::widget

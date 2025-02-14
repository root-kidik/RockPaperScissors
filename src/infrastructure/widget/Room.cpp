#include <infrastructure/storage/Pixmap.hpp>
#include <infrastructure/util/Constant.hpp>
#include <infrastructure/widget/Room.hpp>

namespace rps::infrastructure::widget
{

Room::Room(domain::model::Room& model, const storage::Pixmap& pixmap_storage, domain::entity::User& user) :
m_model{model},
m_pixmap_storage{pixmap_storage},
m_user{user},
m_player_hand{pixmap_storage, HandOfCards::Type::Horizontal, true},
m_east_hand{pixmap_storage, HandOfCards::Type::VerticalRight},
m_west_hand{pixmap_storage, HandOfCards::Type::VerticalLeft},
m_north_hand{pixmap_storage, HandOfCards::Type::Horizontal},
m_table{pixmap_storage, HandOfCards::Type::Horizontal},
m_has_north{},
m_has_west{},
m_has_east{},
m_start_game_button{"Начать игру"}
{
    setLayout(&m_layout);

    m_layout.setAlignment(Qt::AlignCenter);

    m_player_hand.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_east_hand.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_west_hand.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_north_hand.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_table.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_layout.addWidget(&m_north_hand, 0, 1);
    m_layout.addWidget(&m_west_hand, 1, 0);
    m_layout.addWidget(&m_east_hand, 1, 2);
    m_layout.addWidget(&m_player_hand, 2, 1);

    m_layout.addWidget(&m_table, 1, 1);

    m_layout.addWidget(&m_start_game_button, 1, 1);
    m_start_game_button.setHidden(true);

    m_model.subscribe_on_room_creation(
        [this]()
        {
            m_table.setHidden(true);
            m_start_game_button.setHidden(false);
            m_start_game_button.setStyleSheet(util::kDefaultGreenButtonStyle);

            connect(&m_start_game_button,
                    &QPushButton::pressed,
                    [this]()
                    {
                        m_start_game_button.setHidden(true);
                        m_table.setHidden(false);
                    });
        });

    generate_full_backface_deck(m_player_hand);

    m_model.subsribe_on_new_player_addition(
        [this](std::string&& player_nickname)
        {
            if (!m_has_north)
            {
                m_has_north = true;
                generate_full_backface_deck(m_north_hand);
            }
            else if (!m_has_west)
            {
                m_has_west = true;
                generate_full_backface_deck(m_west_hand);
            }
            else if (!m_has_east)
            {
                m_has_east = true;
                generate_full_backface_deck(m_east_hand);
            }
            else
                assert(false && "Added some strange player");
        });
}

void Room::generate_full_backface_deck(HandOfCards& hand)
{
    using namespace rps::protocol::entity;

    for (std::uint8_t i = 0; i < protocol::entity::kMaxCardsPerPlayer; i++)
        hand.add_card(Card::Backface);
}

} // namespace rps::infrastructure::widget

#include <infrastructure/storage/Pixmap.hpp>
#include <infrastructure/util/Constant.hpp>
#include <infrastructure/widget/Room.hpp>

namespace rps::infrastructure::widget
{

Room::Room(domain::model::Room&        model,
           domain::model::HandOfCards& player_hand_of_cards_model,
           domain::model::HandOfCards& north_hand_of_cards_model,
           domain::model::HandOfCards& west_hand_of_cards_model,
           domain::model::HandOfCards& east_hand_of_cards_model,
           domain::model::HandOfCards& play_table_hand_of_cards_model,
           const storage::Pixmap&      pixmap_storage,
           domain::entity::User&       user) :
m_room_model{model},
m_pixmap_storage{pixmap_storage},
m_user{user},
m_player_hand{pixmap_storage, player_hand_of_cards_model, HandOfCards::Type::Horizontal, true},
m_north_hand{pixmap_storage, north_hand_of_cards_model, HandOfCards::Type::Horizontal},
m_west_hand{pixmap_storage, west_hand_of_cards_model, HandOfCards::Type::VerticalLeft},
m_east_hand{pixmap_storage, east_hand_of_cards_model, HandOfCards::Type::VerticalRight},
m_table{pixmap_storage, play_table_hand_of_cards_model, HandOfCards::Type::Horizontal},
m_has_north{},
m_has_west{},
m_has_east{},
m_start_game_button{"Начать игру"}
{
    player_hand_of_cards_model.cards.subscribe_on_update(
        [this](const domain::model::HandOfCards::Card& card, std::size_t idx)
        {
            if (card.is_nominated)
                m_room_model.nominate_card(card.type);
        });

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

    m_room_model.is_room_created.subscribe(
        [this, &player_hand_of_cards_model](const bool& is_room_created)
        {
            if (!is_room_created)
                return;

            m_table.setHidden(true);
            m_start_game_button.setHidden(false);
            m_start_game_button.setStyleSheet(util::kDefaultGreenButtonStyle);

            connect(&m_start_game_button,
                    &QPushButton::pressed,
                    [this, &player_hand_of_cards_model]()
                    {
                        m_start_game_button.setHidden(true);
                        m_table.setHidden(false);
                        m_room_model.start_game();
                        player_hand_of_cards_model.is_locked.set_value(false);
                    });
        });

    generate_full_backface_deck(player_hand_of_cards_model);

    m_room_model.players.subscribe(
        [this, &north_hand_of_cards_model, &west_hand_of_cards_model, &east_hand_of_cards_model](
            const std::string& player_nickname)
        {
            if (!m_has_north)
            {
                m_has_north = true;
                generate_full_backface_deck(north_hand_of_cards_model);
            }
            else if (!m_has_west)
            {
                m_has_west = true;
                generate_full_backface_deck(west_hand_of_cards_model);
            }
            else if (!m_has_east)
            {
                m_has_east = true;
                generate_full_backface_deck(east_hand_of_cards_model);
            }
            else
                assert(false && "Added some strange player");
        });
}

void Room::generate_full_backface_deck(domain::model::HandOfCards& hand_of_cards_model)
{
    using namespace rps::protocol::entity;

    for (std::uint8_t i = 0; i < protocol::entity::kMaxCardsPerPlayer; i++)
        hand_of_cards_model.cards.set_value({Card::Backface, false}, i);
}

} // namespace rps::infrastructure::widget

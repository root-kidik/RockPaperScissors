#include <infrastructure/widget/Room.hpp>

#include <infrastructure/storage/Pixmap.hpp>

#include <infrastructure/util/Constant.hpp>

#include <domain/interface/usecase/StartGame.hpp>

#include <domain/model/HandOfCards.hpp>
#include <domain/model/Room.hpp>

namespace rps::infrastructure::widget
{

Room::Room(domain::model::Room&                   model,
           const storage::Pixmap&                 pixmap_storage,
           domain::entity::User&                  user,
           domain::interface::usecase::StartGame& start_game_usecase) :
m_room_model{model},
m_pixmap_storage{pixmap_storage},
m_user{user},
m_player_hand{pixmap_storage, model.player_hand_of_cards_model, HandOfCards::Type::Horizontal},
m_north_hand{pixmap_storage, model.north_hand_of_cards_model, HandOfCards::Type::Horizontal},
m_west_hand{pixmap_storage, model.west_hand_of_cards_model, HandOfCards::Type::VerticalLeft},
m_east_hand{pixmap_storage, model.east_hand_of_cards_model, HandOfCards::Type::VerticalRight},
m_table{pixmap_storage, model.play_table_hand_of_cards_model, HandOfCards::Type::Horizontal},
m_start_game_button{"Начать игру"},
m_start_game_usecase{start_game_usecase}
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

    m_north_hand.setHidden(true);
    m_west_hand.setHidden(true);
    m_east_hand.setHidden(true);
    m_player_hand.setHidden(true);
    m_table.setHidden(true);

    model.north_hand_of_cards_model.is_visible.subscribe(
        [this](const bool& is_visible) { m_north_hand.setVisible(is_visible); });
    model.west_hand_of_cards_model.is_visible.subscribe(
        [this](const bool& is_visible) { m_west_hand.setVisible(is_visible); });
    model.east_hand_of_cards_model.is_visible.subscribe(
        [this](const bool& is_visible) { m_east_hand.setVisible(is_visible); });
    model.player_hand_of_cards_model.is_visible.subscribe(
        [this](const bool& is_visible) { m_player_hand.setVisible(is_visible); });
    model.play_table_hand_of_cards_model.is_visible.subscribe(
        [this](const bool& is_visible) { m_table.setVisible(is_visible); });

    m_layout.addWidget(&m_table, 1, 1);

    m_room_model.is_room_created.subscribe(
        [this](const bool& is_room_created)
        {
            if (!is_room_created)
                return;

            m_start_game_button.setStyleSheet(util::kDefaultGreenButtonStyle);
            m_start_game_button.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            m_start_game_button.setMaximumSize(util::kMaxButtonSize);

            m_layout.addWidget(&m_start_game_button, 1, 1, Qt::AlignJustify);

            connect(&m_start_game_button, &QPushButton::pressed, [this]() { m_start_game_usecase.start_game(); });
        });

    m_room_model.is_game_started.subscribe(
        [this](const bool& is_game_started)
        {
            if (!is_game_started)
                return;

            m_layout.removeWidget(&m_start_game_button);
            m_start_game_button.setHidden(true);
            m_layout.addWidget(&m_table, 1, 1);
        });
}

} // namespace rps::infrastructure::widget

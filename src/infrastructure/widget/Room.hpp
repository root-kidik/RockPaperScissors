#pragma once

#include <QGridLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include <infrastructure/widget/HandOfCards.hpp>

namespace rps::domain
{

namespace entity
{
struct User;
} // namespace entity

namespace model
{
struct Room;
struct HandOfCards;
} // namespace model

namespace interface::usecase
{
class StartGame;
} // namespace interface::usecase

} // namespace rps::domain

namespace rps::infrastructure::widget
{

class Room final : public QWidget
{
    Q_OBJECT

public:
    Room(domain::model::Room&                   model,
         const storage::Pixmap&                 pixmap_storage,
         domain::entity::User&                  user,
         domain::interface::usecase::StartGame& start_game_usecase);

private:
    domain::model::Room& m_room_model;

    const storage::Pixmap& m_pixmap_storage;
    domain::entity::User&  m_user;

    QGridLayout m_layout;

    HandOfCards m_player_hand;

    HandOfCards m_north_hand;
    HandOfCards m_west_hand;
    HandOfCards m_east_hand;

    HandOfCards m_table;

    QPushButton m_start_game_button;

    domain::interface::usecase::StartGame& m_start_game_usecase;
};

} // namespace rps::infrastructure::widget

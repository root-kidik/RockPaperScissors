#pragma once

#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include <domain/model/RoomSearch.hpp>

namespace rps::infrastructure::widget
{

class RoomSearch : public QWidget
{
    Q_OBJECT

public:
    RoomSearch(protocol::entity::MessageSender&                        message_sender,
               domain::entity::User&                                   user,
               const std::shared_ptr<protocol::interface::Connection>& connection);

private:
    domain::model::RoomSearch m_model;

    QVBoxLayout m_layout;

    QLineEdit   m_room_name_input;
    QPushButton m_create_room_button;
};

} // namespace rps::infrastructure::widget

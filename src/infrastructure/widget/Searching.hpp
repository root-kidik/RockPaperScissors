#pragma once

#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include <domain/model/Searching.hpp>

namespace rps::infrastructure::widget
{

class Searching : public QWidget
{
    Q_OBJECT

public:
    Searching(protocol::entity::MessageSender&                        message_sender,
              domain::entity::User&                                   user,
              const std::shared_ptr<protocol::interface::Connection>& connection);

private:
    domain::model::Searching m_model;

    QVBoxLayout m_layout;

    QLineEdit   m_room_name_input;
    QPushButton m_create_room_button;
};

} // namespace rps::infrastructure::widget

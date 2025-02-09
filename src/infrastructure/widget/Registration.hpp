#pragma once

#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include <domain/entity/User.hpp>

#include <RockPaperScissorsProtocol/entity/MessageSender.hpp>
#include <RockPaperScissorsProtocol/interface/Connection.hpp>

namespace rps::infrastructure::widget
{

class Registration : public QWidget
{
    Q_OBJECT

public:
    Registration(protocol::entity::MessageSender&                        message_sender,
                 domain::entity::User&                                   user,
                 const std::shared_ptr<protocol::interface::Connection>& connection);

private:
    protocol::entity::MessageSender&                        m_message_sender;
    domain::entity::User&                                   m_user;
    const std::shared_ptr<protocol::interface::Connection>& m_connection;

    QVBoxLayout m_layout;

    QLineEdit   m_name_input;
    QPushButton m_register_button;
};

} // namespace rps::infrastructure::widget

#pragma once

#include <QApplication>
#include <QTcpSocket>

#include <domain/entity/Mode.hpp>
#include <domain/entity/User.hpp>

#include <infrastructure/widget/Manager.hpp>

#include <RockPaperScissorsProtocol/entity/MessageSender.hpp>
#include <RockPaperScissorsProtocol/entity/client/ClientMessageExecutor.hpp>

namespace rps::infrastructure
{

class RockPaperScissors
{
public:
    RockPaperScissors(int argc, char* argv[]);

    int run();

private:
    void init_message_handlers();
    void init_widgets();

    QApplication m_app;

    QTcpSocket                                       m_socket;
    protocol::entity::client::ClientMessageExecutor  m_message_executor;
    protocol::entity::MessageSender                  m_message_sender;
    std::shared_ptr<protocol::interface::Connection> m_connection;

    domain::entity::User m_user;

    widget::Manager m_widget_manager;
};

} // namespace rps::infrastructure

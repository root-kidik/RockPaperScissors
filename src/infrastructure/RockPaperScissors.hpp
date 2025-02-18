#pragma once

#include <QApplication>
#include <QTcpSocket>

#include <domain/entity/Mode.hpp>
#include <domain/entity/User.hpp>
#include <domain/model/HandOfCards.hpp>
#include <domain/model/Registration.hpp>
#include <domain/model/Room.hpp>
#include <domain/model/Searching.hpp>

#include <infrastructure/storage/Pixmap.hpp>
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
    void connect_to_server();
    void init_widgets();

    QApplication m_app;

    storage::Pixmap m_pixmap_storage;

    domain::entity::User m_user;

    QTcpSocket                                       m_socket;
    protocol::entity::client::ClientMessageExecutor  m_message_executor;
    protocol::entity::MessageSender                  m_message_sender;
    std::shared_ptr<protocol::interface::Connection> m_connection;

    domain::model::Registration m_registration_model;
    domain::model::Searching    m_searcing_model;

    domain::model::Room m_room_model;

    widget::Manager m_widget_manager;
};

} // namespace rps::infrastructure

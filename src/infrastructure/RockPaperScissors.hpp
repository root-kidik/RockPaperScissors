#pragma once

#include <QApplication>
#include <QTcpSocket>

#include <RockPaperScissorsProtocol/entity/MessageSender.hpp>
#include <RockPaperScissorsProtocol/entity/client/ClientMessageExecutor.hpp>

#include <infrastructure/widget/Manager.hpp>

#include <infrastructure/storage/Pixmap.hpp>

#include <domain/entity/Mode.hpp>
#include <domain/entity/User.hpp>

#include <domain/model/HandOfCards.hpp>
#include <domain/model/Room.hpp>

#include <domain/usecase/Registration.hpp>
#include <domain/usecase/Searching.hpp>
#include <domain/usecase/StartGame.hpp>

namespace rps::infrastructure
{

class RockPaperScissors
{
public:
    RockPaperScissors(int& argc, char* argv[]);

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

    domain::model::Room m_room_model;

    domain::usecase::Registration m_registration_usecase;
    domain::usecase::Searching    m_searcing_usecase;
    domain::usecase::StartGame    m_start_game_usecase;

    widget::Manager m_widget_manager;
};

} // namespace rps::infrastructure

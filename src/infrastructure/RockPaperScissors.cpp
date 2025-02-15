#include <domain/handler/request/GameStarted.hpp>
#include <domain/handler/request/NewPlayerAdded.hpp>
#include <domain/handler/response/ConnectToRoom.hpp>
#include <domain/handler/response/CreateRoom.hpp>
#include <domain/handler/response/Register.hpp>
#include <domain/handler/response/StartGame.hpp>

#include <infrastructure/RockPaperScissors.hpp>
#include <infrastructure/client/TcpSocketConnection.hpp>
#include <infrastructure/widget/MainMenu.hpp>
#include <infrastructure/widget/Registration.hpp>
#include <infrastructure/widget/Room.hpp>
#include <infrastructure/widget/Searching.hpp>

namespace rps::infrastructure
{

RockPaperScissors::RockPaperScissors(int argc, char* argv[]) :
m_app{argc, argv},
m_registration_model{m_message_sender, m_user, m_connection},
m_searcing_model{m_message_sender, m_user, m_connection},
m_room_model{m_message_sender, m_user, m_connection}
{
    init_message_handlers();
    connect_to_server();
    init_widgets();
}

int RockPaperScissors::run()
{
    return m_app.exec();
}

void RockPaperScissors::init_message_handlers()
{
    m_message_executor.register_response_handler<domain::handler::response::Register>(m_user, m_widget_manager);
    m_message_executor.register_response_handler<domain::handler::response::CreateRoom>(m_widget_manager, m_room_model);
    m_message_executor.register_response_handler<domain::handler::response::ConnectToRoom>(m_widget_manager, m_room_model);
    m_message_executor.register_response_handler<domain::handler::response::StartGame>(m_room_model);

    m_message_executor.register_request_handler<domain::handler::request::NewPlayerAdded>(m_room_model);
    m_message_executor.register_request_handler<domain::handler::request::GameStarted>(m_room_model);
}

void RockPaperScissors::connect_to_server()
{
    m_socket.connectToHost("localhost", 1234);
    auto connection_wrapper = std::make_shared<client::TcpSocketConnection>(&m_socket);
    m_connection            = connection_wrapper;

    QObject::connect(&m_socket, &QTcpSocket::disconnected, [connection_wrapper]() { connection_wrapper->disconnect(); });
    QObject::connect(&m_socket,
                     &QTcpSocket::readyRead,
                     [connection_wrapper, this]()
                     { m_message_executor.process_data(m_socket.readAll().toStdString(), connection_wrapper); });
}

void RockPaperScissors::init_widgets()
{
    m_widget_manager.register_widget<widget::MainMenu>(domain::entity::Mode::MainMenu, m_widget_manager);
    m_widget_manager.register_widget<widget::Registration>(domain::entity::Mode::Registration, m_registration_model);
    m_widget_manager.register_widget<widget::Searching>(domain::entity::Mode::Searching, m_searcing_model, m_room_model);
    m_widget_manager.register_widget<widget::Room>(domain::entity::Mode::Room, m_room_model, m_pixmap_storage, m_user);

    m_widget_manager.activate_mode(domain::entity::Mode::MainMenu);
}

} // namespace rps::infrastructure

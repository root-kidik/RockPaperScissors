#include <domain/handler/response/Register.hpp>

#include <infrastructure/RockPaperScissors.hpp>
#include <infrastructure/client/TcpSocketConnection.hpp>
#include <infrastructure/widget/MainMenu.hpp>
#include <infrastructure/widget/Registration.hpp>
#include <infrastructure/widget/RoomSearch.hpp>

namespace rps::infrastructure
{

RockPaperScissors::RockPaperScissors(int argc, char* argv[]) : m_app{argc, argv}
{
    init_message_handlers();
    init_widgets();
}

int RockPaperScissors::run()
{
    return m_app.exec();
}

void RockPaperScissors::init_message_handlers()
{
    m_message_executor.register_response_handler<domain::handler::response::Register>(m_user, m_widget_manager);

    m_socket.connectToHost("localhost", 1234);
    auto connection_wrapper = std::make_shared<client::TcpSocketConnection>(&m_socket);
    m_connection            = connection_wrapper;

    QObject::connect(&m_socket, &QTcpSocket::disconnected, [connection_wrapper]() { connection_wrapper->disconnect(); });
    QObject::connect(&m_socket,
                     &QTcpSocket::readyRead,
                     [connection_wrapper, this]()
                     { m_message_executor.execute_message(m_socket.readAll().toStdString(), connection_wrapper); });
}

void RockPaperScissors::init_widgets()
{
    m_widget_manager.register_widget<widget::MainMenu>(domain::entity::Mode::MainMenu, m_widget_manager);
    m_widget_manager.register_widget<widget::Registration>(domain::entity::Mode::Registration, m_message_sender, m_user, m_connection);
    m_widget_manager.register_widget<widget::RoomSearch>(domain::entity::Mode::RoomSearch);

    m_widget_manager.activate_mode(domain::entity::Mode::MainMenu);
}

} // namespace rps::infrastructure

#include <infrastructure/client/Client.hpp>
#include <infrastructure/client/TcpSocketConnection.hpp>

namespace rps::infrastructure::client
{

Client::Client()
{
    m_socket.connectToHost("localhost", 1234);

    auto connection_wrapper = std::make_shared<client::TcpSocketConnection>(&m_socket);

    connect(&m_socket, &QTcpSocket::disconnected, this, [connection_wrapper]() { connection_wrapper->disconnect(); });

    connect(&m_socket,
            &QTcpSocket::readyRead,
            [connection_wrapper, this]()
            { m_command_executor.execute_command(m_socket.readAll().toStdString(), connection_wrapper); });
}

} // namespace rps::infrastructure::client

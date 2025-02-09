#include <QTcpSocket>

#include <infrastructure/client/TcpSocketConnection.hpp>

namespace rps::infrastructure::client
{

TcpSocketConnection::TcpSocketConnection(QTcpSocket* tcp_socket) : m_tcp_socket{tcp_socket}
{
}

bool TcpSocketConnection::is_connected() const
{
    return m_tcp_socket;
}

void TcpSocketConnection::send(std::string&& data)
{
    assert(m_tcp_socket && "Connection is failed!");

    if (!m_tcp_socket || m_tcp_socket->state() != QAbstractSocket::ConnectedState)
        return;

    m_tcp_socket->write(data.c_str());
    m_tcp_socket->waitForBytesWritten();
}

void TcpSocketConnection::disconnect()
{
    m_tcp_socket = nullptr;
}

} // namespace rps::infrastructure::client

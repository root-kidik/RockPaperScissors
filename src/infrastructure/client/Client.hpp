#pragma once

#include <QTcpSocket>

#include <RockPaperScissorsProtocol/entity/client/ClientMessageExecutor.hpp>

namespace rps::infrastructure::client
{

class Client : public QObject
{
    Q_OBJECT

public:
    Client();

private:
    QTcpSocket m_socket;

    protocol::entity::client::ClientMessageExecutor m_message_executor;
};

} // namespace rps::infrastructure::client

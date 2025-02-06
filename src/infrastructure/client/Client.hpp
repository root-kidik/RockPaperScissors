#pragma once

#include <QTcpSocket>
#include <RockPaperScissorsProtocol/entity/client/ClientCommandExecutor.hpp>

namespace rps::infrastructure::client
{

class Client : public QObject
{
    Q_OBJECT

public:
    Client();

private:
    QTcpSocket m_socket;

    protocol::entity::client::ClientCommandExecutor m_command_executor;
};

} // namespace rps::infrastructure::client

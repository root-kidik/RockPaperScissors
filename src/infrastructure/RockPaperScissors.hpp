#pragma once

#include <QApplication>

#include <infrastructure/client/Client.hpp>
#include <infrastructure/widget/Manager.hpp>
#include <infrastructure/widget/Type.hpp>

#include <RockPaperScissorsProtocol/entity/MessageSender.hpp>

namespace rps::infrastructure
{

class RockPaperScissors
{
public:
    RockPaperScissors(int argc, char* argv[]);

    int run();

private:
    QApplication m_app;

    protocol::entity::MessageSender m_message_sender;
    client::Client                  m_client;

    widget::Manager m_widget_manager;
};

} // namespace rps::infrastructure

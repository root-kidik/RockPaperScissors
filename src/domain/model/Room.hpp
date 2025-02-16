#pragma once

#include <functional>
#include <vector>

#include <domain/entity/User.hpp>
#include <domain/util/Property.hpp>

#include <RockPaperScissorsProtocol/entity/Card.hpp>
#include <RockPaperScissorsProtocol/entity/MessageSender.hpp>
#include <RockPaperScissorsProtocol/interface/Connection.hpp>

namespace rps::domain::model
{

class Room
{
public:
    Room(protocol::entity::MessageSender&                        message_sender,
         domain::entity::User&                                   user,
         const std::shared_ptr<protocol::interface::Connection>& connection);

    util::Property<std::vector<std::string>> players;
    util::Property<std::string>              name;

    util::Property<bool> is_room_created;
    util::Property<bool> is_game_started;

    void start_game();

    void nominate_card(protocol::entity::Card card);

    void subscribe_on_force_nominating_card(std::function<void(protocol::entity::Card)> callback);
    void force_nominate_card(protocol::entity::Card card);

private:
    protocol::entity::MessageSender&                        m_message_sender;
    domain::entity::User&                                   m_user;
    const std::shared_ptr<protocol::interface::Connection>& m_connection;

    std::function<void(protocol::entity::Card)> m_on_card_force_nominated;
};

} // namespace rps::domain::model

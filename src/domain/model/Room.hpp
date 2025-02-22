#pragma once

#include <memory>
#include <string>

#include <RockPaperScissorsProtocol/entity/Card.hpp>

#include <domain/model/HandOfCards.hpp>

#include <domain/util/Property.hpp>

namespace rps
{

namespace protocol
{

namespace entity
{
class MessageSender;
} // namespace entity

namespace interface
{
class Connection;
} // namespace interface

} // namespace protocol

namespace domain::entity
{
struct User;
} // namespace domain::entity

} // namespace rps

namespace rps::domain::model
{

struct Room
{
    Room(protocol::entity::MessageSender&                        message_sender,
         domain::entity::User&                                   user,
         const std::shared_ptr<protocol::interface::Connection>& connection);

    std::array<util::Property<std::string>, protocol::entity::kMaxPlayersPerRoom - 1> players;
    util::Property<std::string>                                                       name;

    util::Property<bool> is_room_created;
    util::Property<bool> is_connected_to_room;
    util::Property<bool> is_game_started;

    util::Property<bool> is_winned;

    domain::model::HandOfCards player_hand_of_cards_model;
    domain::model::HandOfCards north_hand_of_cards_model;
    domain::model::HandOfCards west_hand_of_cards_model;
    domain::model::HandOfCards east_hand_of_cards_model;
    domain::model::HandOfCards play_table_hand_of_cards_model;
};

} // namespace rps::domain::model

#pragma once

#include <vector>

#include <domain/entity/User.hpp>
#include <domain/util/Property.hpp>

#include <RockPaperScissorsProtocol/entity/Card.hpp>
#include <RockPaperScissorsProtocol/entity/MessageSender.hpp>
#include <RockPaperScissorsProtocol/interface/Connection.hpp>

namespace rps::domain::model
{

class HandOfCards;

class Room
{
public:
    Room(domain::model::HandOfCards&                             player_hand_of_cards_model,
         domain::model::HandOfCards&                             north_hand_of_cards_model,
         domain::model::HandOfCards&                             west_hand_of_cards_model,
         domain::model::HandOfCards&                             east_hand_of_cards_model,
         domain::model::HandOfCards&                             play_table_hand_of_cards_model,
         protocol::entity::MessageSender&                        message_sender,
         domain::entity::User&                                   user,
         const std::shared_ptr<protocol::interface::Connection>& connection);

    util::Property<std::vector<std::string>> players;
    util::Property<std::string>              name;

    util::Property<bool> is_room_created;
    util::Property<bool> is_game_started;

    void start_game();

    void force_nominate_card(protocol::entity::Card card);

private:
    void generate_full_backface_deck(domain::model::HandOfCards& hand_of_cards_model);

    domain::model::HandOfCards& m_player_hand_of_cards_model;
    domain::model::HandOfCards& m_north_hand_of_cards_model;
    domain::model::HandOfCards& m_west_hand_of_cards_model;
    domain::model::HandOfCards& m_east_hand_of_cards_model;
    domain::model::HandOfCards& m_play_table_hand_of_cards_model;

    protocol::entity::MessageSender&                        m_message_sender;
    domain::entity::User&                                   m_user;
    const std::shared_ptr<protocol::interface::Connection>& m_connection;

    bool m_has_north;
    bool m_has_west;
    bool m_has_east;
};

} // namespace rps::domain::model

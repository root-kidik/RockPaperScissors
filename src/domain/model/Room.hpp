#pragma once

#include <functional>
#include <vector>

#include <domain/entity/User.hpp>

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

    void start_game();
    void on_game_started();

    void               set_name(std::string&& name);
    [[nodiscard]] const std::string& get_name() const;

    void subscribe_on_room_creation(std::function<void()> callback);
    void create_room();

    void subsribe_on_new_player_addition(std::function<void(std::string&&)> callback);
    void add_new_player(std::string&& player_nickname);

    void nominate_card(protocol::entity::Card card);

    void subscribe_on_user_cards_setted(
        std::function<void(const std::array<protocol::entity::Card, protocol::entity::kMaxCardsPerPlayer>&)> subscriber);
    void set_user_cards(const std::array<protocol::entity::Card, protocol::entity::kMaxCardsPerPlayer>& user_cards);

    void subscribe_on_force_nominating_card(std::function<void(protocol::entity::Card)> callback);
    void force_nominate_card(protocol::entity::Card card);

private:
    protocol::entity::MessageSender&                        m_message_sender;
    domain::entity::User&                                   m_user;
    const std::shared_ptr<protocol::interface::Connection>& m_connection;
    std::function<void(std::string&&)>                      m_on_new_player_added;

    std::function<void()> m_on_room_creation;

    std::vector<std::string> m_players;

    std::string m_name;

    bool m_is_game_started;

    std::function<void(const std::array<protocol::entity::Card, protocol::entity::kMaxCardsPerPlayer>&)> m_on_user_cards_setted;
    std::array<protocol::entity::Card, protocol::entity::kMaxCardsPerPlayer> m_user_cards;
    
    std::function<void(protocol::entity::Card)> m_on_card_force_nominated;
};

} // namespace rps::domain::model

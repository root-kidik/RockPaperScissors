#include <domain/model/Room.hpp>

#include <RockPaperScissorsProtocol/entity/server/request/NominateCard.hpp>
#include <RockPaperScissorsProtocol/entity/server/request/StartGame.hpp>

namespace rps::domain::model
{

Room::Room(protocol::entity::MessageSender&                        message_sender,
           domain::entity::User&                                   user,
           const std::shared_ptr<protocol::interface::Connection>& connection) :
m_message_sender{message_sender},
m_user{user},
m_connection{connection},
m_is_game_started{}
{
}

void Room::start_game()
{
    protocol::entity::server::request::StartGame request;
    request.room_name = m_name;
    request.user_uuid = m_user.uuid;

    m_message_sender.send(std::move(request), m_connection);
}

void Room::on_game_started()
{
    m_is_game_started = true;
}

void Room::set_name(std::string&& name)
{
    m_name = std::move(name);
}

const std::string& Room::get_name() const
{
    return m_name;
}

void Room::subscribe_on_room_creation(std::function<void()> callback)
{
    assert(!m_on_room_creation && "Subcriber already setted!");
    m_on_room_creation = std::move(callback);
}

void Room::create_room()
{
    assert(m_on_room_creation && "Subcriber must be setted!");
    m_on_room_creation();
}

void Room::subsribe_on_new_player_addition(std::function<void(std::string&&)> callback)
{
    assert(!m_on_new_player_added && "Subcriber already setted!");
    m_on_new_player_added = std::move(callback);
}

void Room::add_new_player(std::string&& player_nickname)
{
    m_players.push_back(player_nickname);

    assert(m_on_new_player_added && "Subcriber must be setted!");

    m_on_new_player_added(std::move(player_nickname));
}

void Room::nominate_card(protocol::entity::Card card)
{
    assert(m_is_game_started && "Game must be started!");

    protocol::entity::server::request::NominateCard request;
    request.room_name = m_name;
    request.user_uuid = m_user.uuid;
    request.card      = card;

    m_message_sender.send(std::move(request), m_connection);
}

void Room::subscribe_on_user_cards_setted(
    std::function<void(const std::array<protocol::entity::Card, protocol::entity::kMaxCardsPerPlayer>&)> subscriber)
{
    assert(!m_on_user_cards_setted && "Subcriber already setted!");
    m_on_user_cards_setted = std::move(subscriber); 
}

void Room::set_user_cards(const std::array<protocol::entity::Card, protocol::entity::kMaxCardsPerPlayer>& user_cards) 
{
    assert(m_on_user_cards_setted && "Subscriber must be setted!");
    m_user_cards = user_cards;

    m_on_user_cards_setted(user_cards);
}

void Room::subscribe_on_force_nominating_card(std::function<void(protocol::entity::Card)> callback)
{
    assert(!m_on_card_force_nominated && "Subcriber already setted!");
    m_on_card_force_nominated = std::move(callback);
}

void Room::force_nominate_card(protocol::entity::Card card)
{
    assert(m_on_card_force_nominated && "Subscriber must be setted!");
    m_on_card_force_nominated(card);
}

} // namespace rps::domain::model

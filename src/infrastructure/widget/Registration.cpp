#include <infrastructure/widget/Registration.hpp>

#include <RockPaperScissorsProtocol/entity/server/request/Register.hpp>

namespace rps::infrastructure::widget
{

Registration::Registration(protocol::entity::MessageSender&                        message_sender,
                           domain::entity::User&                                   user,
                           const std::shared_ptr<protocol::interface::Connection>& connection) :
m_message_sender{message_sender},
m_user{user},
m_connection{connection},
m_name_input{"Ваше имя"},
m_register_button{"Зарегистрироваться"}
{
    setLayout(&m_layout);

    connect(&m_register_button,
            &QPushButton::pressed,
            [this]()
            {
                m_user.nickname = m_name_input.text().toStdString();

                protocol::entity::server::request::Register request;
                request.user_nickname = m_name_input.text().toStdString();

                m_message_sender.send(std::move(request), m_connection);
            });

    m_layout.addWidget(&m_name_input);
    m_layout.addWidget(&m_register_button);
}

} // namespace rps::infrastructure::widget

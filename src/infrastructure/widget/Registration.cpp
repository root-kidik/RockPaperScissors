#include <infrastructure/widget/Registration.hpp>

namespace rps::infrastructure::widget
{

Registration::Registration(protocol::entity::MessageSender&                        message_sender,
                           domain::entity::User&                                   user,
                           const std::shared_ptr<protocol::interface::Connection>& connection) :
m_model{message_sender, user, connection},
m_name_input{"Ваше имя"},
m_register_button{"Зарегистрироваться"}
{
    setLayout(&m_layout);

    connect(&m_register_button,
            &QPushButton::pressed,
            [this]() { m_model.registrate(m_name_input.text().toStdString()); });

    m_layout.addWidget(&m_name_input);
    m_layout.addWidget(&m_register_button);
}

} // namespace rps::infrastructure::widget

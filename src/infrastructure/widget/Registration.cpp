#include <infrastructure/widget/Registration.hpp>

namespace rps::infrastructure::widget
{

Registration::Registration() : m_name_input{"Что это"}, m_register_button{"Зарегистрироваться"}
{
    setLayout(&m_layout);

    connect(&m_register_button, &QPushButton::pressed, [this]() { auto name = m_name_input.text().toStdString(); });

    m_layout.addWidget(&m_name_input);
    m_layout.addWidget(&m_register_button);
}

} // namespace rps::infrastructure::widget

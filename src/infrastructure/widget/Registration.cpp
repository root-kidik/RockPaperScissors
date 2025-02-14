#include <infrastructure/util/Constant.hpp>
#include <infrastructure/widget/Registration.hpp>

namespace rps::infrastructure::widget
{

Registration::Registration(domain::model::Registration& model) : m_model{model}, m_register_button{"Зарегистрироваться"}
{
    setLayout(&m_layout);

    m_layout.setAlignment(Qt::AlignCenter);

    m_name_input.setPlaceholderText("Введите ваше имя");

    m_name_input.setStyleSheet(util::kDefaultLineEditStyle);
    m_register_button.setStyleSheet(util::kDefaultGreenButtonStyle);

    m_name_input.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_register_button.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_name_input.setMaximumSize(util::kMaxButtonSize);
    m_register_button.setMaximumSize(util::kMaxButtonSize);

    connect(&m_register_button,
            &QPushButton::pressed,
            [this]() { m_model.registrate(m_name_input.text().toStdString()); });

    m_layout.addWidget(&m_name_input);
    m_layout.addWidget(&m_register_button);
}

} // namespace rps::infrastructure::widget

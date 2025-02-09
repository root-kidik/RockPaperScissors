#pragma once

#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include <domain/model/Registration.hpp>

namespace rps::infrastructure::widget
{

class Registration : public QWidget
{
    Q_OBJECT

public:
    Registration(protocol::entity::MessageSender&                        message_sender,
                 domain::entity::User&                                   user,
                 const std::shared_ptr<protocol::interface::Connection>& connection);

private:
    domain::model::Registration m_model;

    QVBoxLayout m_layout;

    QLineEdit   m_name_input;
    QPushButton m_register_button;
};

} // namespace rps::infrastructure::widget

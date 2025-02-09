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
    Registration(domain::model::Registration& model);

private:
    domain::model::Registration& m_model;

    QVBoxLayout m_layout;

    QLineEdit   m_name_input;
    QPushButton m_register_button;
};

} // namespace rps::infrastructure::widget

#pragma once

#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include <domain/model/Registration.hpp>

#include <infrastructure/widget/NoSpaceLineEdit.hpp>

namespace rps::infrastructure::widget
{

class Registration final : public QWidget
{
    Q_OBJECT

public:
    Registration(domain::model::Registration& model);

private:
    domain::model::Registration& m_model;

    QVBoxLayout m_layout;

    NoSpaceLineEdit m_name_input;
    QPushButton     m_register_button;
};

} // namespace rps::infrastructure::widget

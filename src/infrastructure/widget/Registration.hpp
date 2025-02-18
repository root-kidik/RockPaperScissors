#pragma once

#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include <infrastructure/widget/NoSpaceLineEdit.hpp>

namespace rps::domain::usecase
{
class Registration;
}

namespace rps::infrastructure::widget
{

class Registration final : public QWidget
{
    Q_OBJECT

public:
    Registration(domain::usecase::Registration& usecase);

private:
    domain::usecase::Registration& m_usecase;

    QVBoxLayout m_layout;

    NoSpaceLineEdit m_name_input;
    QPushButton     m_register_button;
};

} // namespace rps::infrastructure::widget

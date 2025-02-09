#pragma once

#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

namespace rps::infrastructure::widget
{

class Registration : public QWidget
{
    Q_OBJECT

public:
    Registration();

private:
    QVBoxLayout m_layout;

    QLineEdit   m_name_input;
    QPushButton m_register_button;
};

} // namespace rps::infrastructure::widget

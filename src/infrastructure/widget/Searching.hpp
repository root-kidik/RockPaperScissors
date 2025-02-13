#pragma once

#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include <domain/model/Searching.hpp>

#include <infrastructure/widget/NoSpaceLineEdit.hpp>

namespace rps::infrastructure::widget
{

class Searching : public QWidget
{
    Q_OBJECT

public:
    Searching(domain::model::Searching& model);

private:
    domain::model::Searching m_model;

    QVBoxLayout m_layout;

    NoSpaceLineEdit m_room_name_input;
    QPushButton     m_create_room_button;
    QPushButton     m_connect_to_room_button;
};

} // namespace rps::infrastructure::widget

#pragma once

#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include <infrastructure/widget/NoSpaceLineEdit.hpp>

namespace rps::domain
{

namespace model
{
struct Room;
} // namespace model

namespace usecase
{
class Searching;
} // namespace usecase

} // namespace rps::domain

namespace rps::infrastructure::widget
{

class Searching final : public QWidget
{
    Q_OBJECT

public:
    Searching(domain::usecase::Searching& usecase, domain::model::Room& room);

private:
    domain::usecase::Searching& m_usecase;
    domain::model::Room&        m_room;

    QVBoxLayout m_layout;

    NoSpaceLineEdit m_room_name_input;
    QPushButton     m_create_room_button;
    QPushButton     m_connect_to_room_button;
};

} // namespace rps::infrastructure::widget

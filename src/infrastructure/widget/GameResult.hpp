#pragma once

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

namespace rps::domain::model
{
struct Room;
} // namespace rps::domain::model

namespace rps::infrastructure::widget
{

class Manager;

class GameResult final : public QWidget
{
    Q_OBJECT

public:
    GameResult(domain::model::Room& room);

private:
    QVBoxLayout m_layout;
    QLabel      m_text;
    QPushButton m_quit_button;
};

} // namespace rps::infrastructure::widget

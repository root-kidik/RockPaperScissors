#pragma once

#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

namespace rps::infrastructure::widget
{

class Manager;

class MainMenu : public QWidget
{
    Q_OBJECT

public:
    MainMenu(widget::Manager& widget_manager);

private:
    widget::Manager& m_widget_manager;

    QVBoxLayout m_layout;

    QPushButton m_start_game_button;
    QPushButton m_quit_button;
};

} // namespace rps::infrastructure::widget

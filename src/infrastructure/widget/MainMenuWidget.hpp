#pragma once

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

namespace rps::infrastructure::widget
{

class MainMenuWidget : public QWidget
{
    Q_OBJECT

public:
    MainMenuWidget();
    ~MainMenuWidget();
};

} // namespace rps::infrastructure::widget

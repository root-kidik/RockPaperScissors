#pragma once

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include <domain/model/Room.hpp>

namespace rps::infrastructure::widget
{

class Room : public QGraphicsView
{
    Q_OBJECT

public:
    Room(domain::model::Room& model);

private:
    domain::model::Room& m_model;

    QGraphicsScene m_scene;
};

} // namespace rps::infrastructure::widget

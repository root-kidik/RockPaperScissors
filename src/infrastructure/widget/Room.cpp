#include <QGraphicsPixmapItem>

#include <infrastructure/widget/Room.hpp>

namespace rps::infrastructure::widget
{

Room::Room(domain::model::Room& model) : m_model{model}
{
    setScene(&m_scene);
    setFixedSize(800, 600);

    QPixmap pixmap(":/assets/Rock.png");

    auto* item = m_scene.addPixmap(pixmap);
    item->setPos(0, 50);

    m_model.subsribe_on_new_player_addition(
        [this](std::string&& player_nickname)
        {
            // TODO(@rtkid): handle
        });
}

} // namespace rps::infrastructure::widget

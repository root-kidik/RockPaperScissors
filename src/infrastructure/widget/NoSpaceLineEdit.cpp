#include <infrastructure/widget/NoSpaceLineEdit.hpp>

namespace rps::infrastructure::widget
{

void NoSpaceLineEdit::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Space)
        return;

    QLineEdit::keyPressEvent(event);
}

} // namespace rps::infrastructure::widget

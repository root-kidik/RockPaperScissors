#pragma once

#include <QKeyEvent>
#include <QLineEdit>

namespace rps::infrastructure::widget
{

class NoSpaceLineEdit final : public QLineEdit
{
public:
    using QLineEdit::QLineEdit;

protected:
    void keyPressEvent(QKeyEvent* event) override;
};

} // namespace rps::infrastructure::widget

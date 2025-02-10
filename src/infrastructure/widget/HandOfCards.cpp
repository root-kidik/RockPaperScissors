#include <QApplication>
#include <QHBoxLayout>
#include <QScreen>
#include <QVBoxLayout>

#include <cassert>

#include <infrastructure/storage/Pixmap.hpp>
#include <infrastructure/widget/HandOfCards.hpp>

namespace rps::infrastructure::widget
{

HandOfCards::HandOfCards(const storage::Pixmap& pixmap_storage, Type type) :
m_pixmap_storage{pixmap_storage},
m_cards_count{},
m_type{type}
{
    QLayout* layout;

    bool is_vertical = m_type == Type::VerticalLeft || m_type == Type::VerticalRight;

    if (is_vertical)
        layout = new QVBoxLayout;
    else
        layout = new QHBoxLayout;

    setLayout(layout);

    auto screen_size = QApplication::primaryScreen()->size();

    std::uint32_t maximum_height = screen_size.height() / 4 / 2;
    std::uint32_t maximum_width  = screen_size.width() / m_cards.size() / 2 / 2;

    if (is_vertical)
        std::swap(maximum_height, maximum_width);

    for (auto& card : m_cards)
    {
        card.setMaximumHeight(maximum_height);
        card.setMaximumWidth(maximum_width);
    }
}

void HandOfCards::add_card(protocol::entity::Card card)
{
    assert(m_cards_count != m_cards.size() && "Too many cards added");

    auto& card_widget = m_cards[m_cards_count];

    const auto& original_pixmap = m_pixmap_storage.get(card);

    if (m_type == Type::VerticalLeft)
    {
        QTransform transform;
        transform.rotate(-90);

        card_widget.setIcon(original_pixmap.transformed(transform, Qt::SmoothTransformation));
    }
    else if (m_type == Type::VerticalRight)
    {
        QTransform transform;
        transform.rotate(90);

        card_widget.setIcon(original_pixmap.transformed(transform, Qt::SmoothTransformation));
    }
    else
        card_widget.setIcon(original_pixmap);

    card_widget.setIconSize(card_widget.size());

    layout()->addWidget(&card_widget);

    m_cards_count++;
}

} // namespace rps::infrastructure::widget

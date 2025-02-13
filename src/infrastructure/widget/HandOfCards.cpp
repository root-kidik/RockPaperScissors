#include <cassert>

#include <infrastructure/storage/Pixmap.hpp>
#include <infrastructure/widget/HandOfCards.hpp>

namespace
{
constexpr std::uint32_t kBaseWidthCard  = 90;
constexpr std::uint32_t kBaseHeightCard = 160;

constexpr std::int8_t kVerticalLeftRotate  = -90;
constexpr std::int8_t kVerticalRightRotate = 90;
} // namespace

namespace rps::infrastructure::widget
{

HandOfCards::HandOfCards(const storage::Pixmap& pixmap_storage, Type type) :
m_pixmap_storage{pixmap_storage},
m_cards_count{},
m_type{type}
{
    QLayout* layout;

    if (m_type != Type::Horizontal)
        layout = new QVBoxLayout;
    else
        layout = new QHBoxLayout;

    setLayout(layout);

    for (auto& card : m_cards)
        card.setStyleSheet("QPushButton { border: none; padding: 0; }");
}

void HandOfCards::add_card(protocol::entity::Card card)
{
    assert(m_cards_count != m_cards.size() && "Too many cards added");

    auto& card_widget = m_cards[m_cards_count];

    const auto& original_pixmap = m_pixmap_storage.get(card);

    if (m_type == Type::VerticalLeft)
    {
        QTransform transform;
        transform.rotate(kVerticalLeftRotate);

        card_widget.setIcon(original_pixmap.transformed(transform, Qt::SmoothTransformation));
    }
    else if (m_type == Type::VerticalRight)
    {
        QTransform transform;
        transform.rotate(kVerticalRightRotate);

        card_widget.setIcon(original_pixmap.transformed(transform, Qt::SmoothTransformation));
    }
    else
        card_widget.setIcon(original_pixmap);

    if (m_type == Type::Horizontal)
        card_widget.setIconSize({kBaseWidthCard, kBaseHeightCard});
    else
        card_widget.setIconSize({kBaseHeightCard, kBaseWidthCard});

    layout()->addWidget(&card_widget);

    m_cards_count++;
}

} // namespace rps::infrastructure::widget

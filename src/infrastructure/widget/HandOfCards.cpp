#include <cassert>

#include <infrastructure/storage/Pixmap.hpp>
#include <infrastructure/widget/HandOfCards.hpp>

namespace
{
constexpr std::uint32_t kBaseWidthCard  = 72;
constexpr std::uint32_t kBaseHeightCard = 128;

constexpr std::int8_t kVerticalLeftRotate  = -90;
constexpr std::int8_t kVerticalRightRotate = 90;

constexpr const char* kDefaultCardStyle =
    "QPushButton {"
    "background-color:rgb(76, 175, 80);"
    "border-radius: 10px;"
    "padding: 10px;"
    "}"
    "QPushButton:hover {"
    "background-color:rgb(32, 146, 37);"
    "}";

constexpr const char* kPressedCardStyle =
    "QPushButton {"
    "background-color:rgb(22, 102, 26);"
    "border-radius: 10px;"
    "padding: 10px;"
    "}";

constexpr QSize kMaxAdditionSize{20, 20};

} // namespace

namespace rps::infrastructure::widget
{

HandOfCards::HandOfCards(const storage::Pixmap& pixmap_storage, Type type, bool is_player_deck) :
m_pixmap_storage{pixmap_storage},
m_cards_count{},
m_type{type},
m_is_player_deck{is_player_deck}
{
    QLayout* layout;

    if (m_type != Type::Horizontal)
        layout = new QVBoxLayout;
    else
        layout = new QHBoxLayout;

    setLayout(layout);

    layout->setAlignment(Qt::AlignCenter);
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

    card_widget.setStyleSheet(kDefaultCardStyle);

    QSize size;
    if (m_type == Type::Horizontal)
        size = {kBaseWidthCard, kBaseHeightCard};
    else
        size = {kBaseHeightCard, kBaseWidthCard};

    card_widget.setIconSize(size);
    card_widget.setMaximumSize(size + kMaxAdditionSize);

    layout()->addWidget(&card_widget);

    m_cards_count++;

    if (!m_is_player_deck)
        return;

    connect(&card_widget,
            &QPushButton::pressed,
            [this, &card_widget]()
            {
                for (auto& card : m_cards)
                    card.setStyleSheet(kDefaultCardStyle);

                card_widget.setStyleSheet(kPressedCardStyle);
            });
}

} // namespace rps::infrastructure::widget

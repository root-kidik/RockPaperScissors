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

    auto& [button, type] = m_cards[m_cards_count];
    type                 = card;

    const auto& original_pixmap = m_pixmap_storage.get(card);

    if (m_type == Type::VerticalLeft)
    {
        QTransform transform;
        transform.rotate(kVerticalLeftRotate);

        button.setIcon(original_pixmap.transformed(transform, Qt::SmoothTransformation));
    }
    else if (m_type == Type::VerticalRight)
    {
        QTransform transform;
        transform.rotate(kVerticalRightRotate);

        button.setIcon(original_pixmap.transformed(transform, Qt::SmoothTransformation));
    }
    else
        button.setIcon(original_pixmap);

    button.setStyleSheet(kDefaultCardStyle);

    QSize size;
    if (m_type == Type::Horizontal)
        size = {kBaseWidthCard, kBaseHeightCard};
    else
        size = {kBaseHeightCard, kBaseWidthCard};

    button.setIconSize(size);
    button.setMaximumSize(size + kMaxAdditionSize);

    layout()->addWidget(&button);

    auto card_idx = m_cards_count++;

    if (!m_is_player_deck)
        return;

    assert(m_on_card_selected && "Callback must be not nullptr");

    connect(&button,
            &QPushButton::pressed,
            [this, &button, card_idx]()
            {
                for (auto& [btn, type] : m_cards)
                    btn.setStyleSheet(kDefaultCardStyle);

                button.setStyleSheet(kPressedCardStyle);

                m_on_card_selected(m_cards[card_idx].type, card_idx);
            });
}

void HandOfCards::replace_card(CardIdx idx, protocol::entity::Card card)
{
    auto& [button, type] = m_cards[idx]; 
    button.setIcon(m_pixmap_storage.get(card));
    type = card;
}

void HandOfCards::replace_by_value_to_backface(protocol::entity::Card card)
{
    auto it = std::find_if(m_cards.begin(), m_cards.end(), [card](const auto& val) { return val.type == card; });

    assert(it != m_cards.end() && "Card must be exist");

    it->button.setIcon(m_pixmap_storage.get(protocol::entity::Card::Backface));
    it->type = card;
}

void HandOfCards::subscribe_on_card_selection(std::function<void(protocol::entity::Card, CardIdx)> callback)
{
    assert(!m_on_card_selected && "Subscriber must be nullptr");

    m_on_card_selected = std::move(callback);
}

} // namespace rps::infrastructure::widget

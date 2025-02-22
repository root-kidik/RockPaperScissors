#include <infrastructure/widget/HandOfCards.hpp>

#include <infrastructure/storage/Pixmap.hpp>

#include <domain/model/HandOfCards.hpp>

namespace
{

constexpr std::uint32_t kBaseWidthCard  = 72;
constexpr std::uint32_t kBaseHeightCard = 128;

constexpr std::int8_t kVerticalLeftRotate  = -90;
constexpr std::int8_t kVerticalRightRotate = 90;

constexpr const char* kDefaultCardStyle =
    "QPushButton {"
    "background-color:rgb(137, 102, 160);"
    "border-radius: 10px;"
    "padding: 10px;"
    "}"
    "QPushButton:hover {"
    "background-color:rgb(83, 50, 105);"
    "}";

constexpr const char* kPressedCardStyle =
    "QPushButton {"
    "background-color:rgb(57, 33, 73);"
    "border-radius: 10px;"
    "padding: 10px;"
    "}";

constexpr const char* kWinCardStyle = 
    "QPushButton {"
    "background-color:rgb(21, 68, 7);"
    "border-radius: 10px;"
    "padding: 10px;"
    "}";

constexpr const char* kLoseCardStyle =
    "QPushButton {"
    "background-color:rgb(75, 3, 3);"
    "border-radius: 10px;"
    "padding: 10px;"
    "}";

constexpr QSize kMaxAdditionSize{20, 20};

} // namespace

namespace rps::infrastructure::widget
{

HandOfCards::HandOfCards(const storage::Pixmap& pixmap_storage, domain::model::HandOfCards& model, Type type) :
m_pixmap_storage{pixmap_storage},
m_model{model},
m_type{type}
{
    QLayout* new_layout;

    if (m_type != Type::Horizontal)
        new_layout = new QVBoxLayout;
    else
        new_layout = new QHBoxLayout;

    setLayout(new_layout);

    layout()->setAlignment(Qt::AlignCenter);

    assert(m_model.cards.size() == m_buttons.size() && "size must be equal");

    for (std::size_t i = 0; i < m_model.cards.size(); i++)
    {
        auto& card   = m_model.cards[i];
        auto& button = m_buttons[i];

        const auto& original_pixmap = m_pixmap_storage.get(card.type.get_value());

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
        button.setHidden(m_model.is_backface_hidden.get_value() && card.type.get_value() == protocol::entity::Card::Backface);

        layout()->addWidget(&button);

        connect(&button, &QPushButton::pressed, [this, &card]() { card.is_nominated.set_value(true); });

        card.is_nominated.subscribe(
            [this, &card, &button](const bool& is_nominated)
            {
                for (auto& btn : m_buttons)
                    btn.setStyleSheet(kDefaultCardStyle);

                button.setStyleSheet(is_nominated ? kPressedCardStyle : kDefaultCardStyle);
            });

        card.is_force_nominated.subscribe(
            [this, &card, &button](const bool& is_force_nominated)
            {
                for (auto& btn : m_buttons)
                    btn.setStyleSheet(kDefaultCardStyle);

                button.setStyleSheet(is_force_nominated ? kPressedCardStyle : kDefaultCardStyle);
            });

        card.is_raised.subscribe([this, &card, &button](const bool& is_raised) { button.setHidden(is_raised); });

        card.type.subscribe(
            [this, &card, &button](const protocol::entity::Card& type)
            {
                button.setHidden(
                    card.is_raised.get_value() ||
                    (m_model.is_backface_hidden.get_value() && card.type.get_value() == protocol::entity::Card::Backface));
                button.setIcon(m_pixmap_storage.get(type));
            });

        card.raise_status.subscribe([this, &card, &button](const domain::model::HandOfCards::Card::RaiseStatus& status){
            if (status == domain::model::HandOfCards::Card::RaiseStatus::NotChoosen)
            {
                button.setStyleSheet(kDefaultCardStyle);
                return;
            }
            
            button.setStyleSheet(status == domain::model::HandOfCards::Card::RaiseStatus::Win ? kWinCardStyle : kLoseCardStyle);
        });
    };
}

} // namespace rps::infrastructure::widget

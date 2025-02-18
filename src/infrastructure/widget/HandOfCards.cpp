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

HandOfCards::HandOfCards(const storage::Pixmap& pixmap_storage, domain::model::HandOfCards& model, Type type) :
m_pixmap_storage{pixmap_storage},
m_model{model},
m_type{type}
{
    m_model.cards.subscribe_on_add(
        [this, &model](const domain::model::HandOfCards::Card& card, std::size_t idx)
        {
            auto& button = m_buttons[idx];

            const auto& original_pixmap = m_pixmap_storage.get(card.type);

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

            connect(&button,
                    &QPushButton::pressed,
                    [this, &model, idx]() { model.cards.update_value({model.cards.get_value(idx).type, true}, idx); });
        });

    m_model.cards.subscribe_on_update(
        [this](const domain::model::HandOfCards::Card& card, std::size_t idx)
        {
            auto& button = m_buttons[idx];

            for (auto& btn : m_buttons)
                btn.setStyleSheet(kDefaultCardStyle);

            button.setIcon(m_pixmap_storage.get(card.type));
            button.setStyleSheet(card.is_nominated ? kPressedCardStyle : kDefaultCardStyle);
        });

    QLayout* layout;

    if (m_type != Type::Horizontal)
        layout = new QVBoxLayout;
    else
        layout = new QHBoxLayout;

    setLayout(layout);

    layout->setAlignment(Qt::AlignCenter);
}

} // namespace rps::infrastructure::widget

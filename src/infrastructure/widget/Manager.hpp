#pragma once

#include <QStackedWidget>

#include <cassert>
#include <infrastructure/widget/Type.hpp>
#include <memory>
#include <unordered_map>

namespace rps::infrastructure::widget
{

class Manager
{
public:
    Manager()
    {
        m_stacked_widget.show();
    }

    void activate_widget(Type widget_type)
    {
        assert(m_widgets.find(widget_type) != m_widgets.end() && "Not setted widget to activate this widget_type");

        m_stacked_widget.setCurrentWidget(m_widgets[widget_type].get());
    }

    template <typename Widget, typename... Args>
    void register_widget(Type widget_type, Args&&... args)
    {
        assert(m_widgets.find(widget_type) == m_widgets.end() && "Already setted widget to this widget_type");

        auto widget = std::make_unique<Widget>(std::forward<Args>(args)...);

        m_stacked_widget.addWidget(widget.get());
        m_widgets.emplace(widget_type, std::move(widget));
    }

private:
    QStackedWidget                                     m_stacked_widget;
    std::unordered_map<Type, std::unique_ptr<QWidget>> m_widgets;
};

} // namespace rps::infrastructure::widget

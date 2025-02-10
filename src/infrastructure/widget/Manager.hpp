#pragma once

#include <QStackedWidget>

#include <cassert>
#include <memory>
#include <unordered_map>

#include <domain/interface/ModeManager.hpp>

namespace rps::infrastructure::widget
{

class Manager : public domain::interface::ModeManager
{
public:
    Manager()
    {
        m_stacked_widget.showFullScreen();
    }

    void activate_mode(domain::entity::Mode mode) override
    {
        assert(m_widgets.find(mode) != m_widgets.end() && "Not setted widget to activate this mode");

        m_stacked_widget.setCurrentWidget(m_widgets[mode].get());
    }

    template <typename Widget, typename... Args>
    void register_widget(domain::entity::Mode mode, Args&&... args)
    {
        assert(m_widgets.find(mode) == m_widgets.end() && "Already setted widget to this mode");

        auto widget = std::make_unique<Widget>(std::forward<Args>(args)...);

        m_stacked_widget.addWidget(widget.get());
        m_widgets.emplace(mode, std::move(widget));
    }

private:
    QStackedWidget                                                     m_stacked_widget;
    std::unordered_map<domain::entity::Mode, std::unique_ptr<QWidget>> m_widgets;
};

} // namespace rps::infrastructure::widget

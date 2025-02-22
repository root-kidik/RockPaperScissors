#pragma once

#include <cassert>
#include <functional>
#include <vector>

namespace rps::domain::util
{

template <typename T>
class Property
{
public:
    using ValidateFn = std::function<bool(const T&)>;
    using CallbackFn = std::function<void(const T&)>;

    Property(ValidateFn validate_callback = nullptr) : m_validate_callback{std::move(validate_callback)}
    {
    }

    Property(T value, ValidateFn validate_callback = nullptr) :
    m_validate_callback{std::move(validate_callback)},
    m_value{std::move(value)}
    {
#ifndef NDEBUG
        m_is_value_setted = true;
#endif
    }

    void subscribe(CallbackFn callback)
    {
        assert(callback != nullptr && "callback must be not nullptr");

        m_subscribers.push_back(std::move(callback));
    }

    const T& get_value() const
    {
        assert(m_is_value_setted && "value not yet setted!");
        return m_value;
    }

    void set_value(T value)
    {
#ifndef NDEBUG
        m_is_value_setted = true;
#endif

        if (m_validate_callback && !m_validate_callback(value))
            return;

        m_value = std::move(value);

        for (auto& subscriber : m_subscribers)
            subscriber(m_value);
    }

private:
    ValidateFn m_validate_callback;

    T m_value;

#ifndef NDEBUG
    bool m_is_value_setted{};
#endif

    std::vector<CallbackFn> m_subscribers;
};

} // namespace rps::domain::util

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

template <typename T>
class Property<std::vector<T>>
{
public:
    using ValidateFn       = std::function<bool(const T&, std::size_t)>;
    using CallbackFn       = std::function<void(const T&, std::size_t)>;

    Property(ValidateFn validate_on_add_callback = nullptr, ValidateFn validate_on_update_callback = nullptr) :
    m_validate_on_add_callback{std::move(validate_on_add_callback)},
    m_validate_on_update_callback{std::move(validate_on_update_callback)}
    {
    }

    void subscribe_on_add(CallbackFn callback)
    {
        assert(callback != nullptr && "callback must be not nullptr");

        m_on_add_subscribers.push_back(std::move(callback));
    }

    void subscribe_on_update(CallbackFn callback)
    {
        assert(callback != nullptr && "callback must be not nullptr");

        m_on_update_subscribers.push_back(std::move(callback));
    }

    void add_value(T value)
    {
        const auto sz = size();

        if (m_validate_on_add_callback && !m_validate_on_add_callback(value, sz))
            return;

        m_values.push_back(std::move(value));

        for (auto& subscriber : m_on_add_subscribers)
            subscriber(m_values.back(), sz);
    }

    void update_value(T value, std::size_t idx)
    {
        assert(idx >= 0 && "idx must be greater or equal 0");
        assert(idx < size() && "idx must be less than size");

        if (m_validate_on_update_callback && !m_validate_on_update_callback(value, idx))
            return;

        m_values[idx] = std::move(value);

        for (auto& subscriber : m_on_update_subscribers)
            subscriber(m_values[idx], idx);
    }

    const T& get_value(std::size_t idx)
    {
        assert(idx >= 0 && "idx must be greater or equal 0");
        assert(idx < size() && "idx must be less than size");

        return m_values[idx];
    }

    std::size_t size()
    {
        return m_values.size();
    }

private:
    ValidateFn m_validate_on_add_callback;
    ValidateFn m_validate_on_update_callback;

    std::vector<T> m_values;

    std::vector<CallbackFn>       m_on_add_subscribers;
    std::vector<CallbackFn>       m_on_update_subscribers;
};

} // namespace rps::domain::util

#pragma once

#include <array>
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

    Property(T value, ValidateFn validate_callback = nullptr) : m_validate_callback{std::move(validate_callback)}, m_value{std::move(value)}
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

        for (auto& subscriber : m_subscribers)
            subscriber(value);

        m_value = std::move(value);
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
    using ValidateFn = std::function<bool(const T&)>;
    using CallbackFn = std::function<void(const T&)>;

    Property(ValidateFn validate_callback = nullptr) : m_validate_callback{std::move(validate_callback)}
    {
    }

    void subscribe(CallbackFn callback)
    {
        assert(callback != nullptr && "callback must be not nullptr");

        m_subscribers.push_back(std::move(callback));
    }

    void add_value(T value)
    {
        if (m_validate_callback && !m_validate_callback(value))
            return;

        for (auto& subscriber : m_subscribers)
            subscriber(value);

        m_values.push_back(std::move(value));
    }

private:
    ValidateFn m_validate_callback;


    std::vector<T> m_values;

    std::vector<CallbackFn> m_subscribers;
};

template <typename T, std::size_t Size>
class Property<std::array<T, Size>>
{
public:
    using ValidateFn = std::function<bool(const T&)>;
    using CallbackFn = std::function<void(const T&, std::size_t)>;

    Property(ValidateFn validate_callback_on_set = nullptr, ValidateFn validate_callback_on_update = nullptr) :
    m_validate_callback_on_set{std::move(validate_callback_on_set)},
    m_validate_callback_on_update{std::move(validate_callback_on_update)}
    {
    }

    void subscribe_on_set(CallbackFn callback)
    {
        assert(callback != nullptr && "callback must be not nullptr");

        m_on_set_subscribers.push_back(std::move(callback));
    }

    void set_value(T value, std::size_t idx)
    {
        assert(idx >= 0 && "idx must be greater or equal 0");
        assert(idx < Size && "idx must be less than size");

#ifndef NDEBUG
        m_setted_idxs = std::min(m_setted_idxs + 1, Size);
#endif

        assert(idx < m_setted_idxs && "you tried set value, that already setted");

        if (m_validate_callback_on_set && !m_validate_callback_on_set(value))
            return;

        for (auto& subscriber : m_on_set_subscribers)
            subscriber(value, idx);

        m_values[idx] = std::move(value);
    }

    void subscribe_on_update(CallbackFn callback)
    {
        assert(callback != nullptr && "callback must be not nullptr");

        m_on_update_subscribers.push_back(std::move(callback));
    }

    void update_value(T value, std::size_t idx)
    {
        assert(idx >= 0 && "idx must be greater or equal than 0");
        assert(idx < Size && "idx must be less than size");

#ifndef NDEBUG
        assert(idx < m_setted_idxs && "you tried update value, that not yet setted");
#endif

        if (m_validate_callback_on_update && !m_validate_callback_on_update(value))
            return;

        for (auto& subscriber : m_on_update_subscribers)
            subscriber(value, idx);

        m_values[idx] = std::move(value);
    }

    const T& get_value(std::size_t idx) const
    {
#ifndef NDEBUG
        assert(idx < m_setted_idxs && "you tried get value, that not yet setted");
#endif

        return m_values[idx];
    }

private:
    ValidateFn m_validate_callback_on_set;
    ValidateFn m_validate_callback_on_update;

    std::array<T, Size> m_values;

#ifndef NDEBUG
    std::size_t m_setted_idxs{};
#endif

    std::vector<CallbackFn> m_on_set_subscribers;
    std::vector<CallbackFn> m_on_update_subscribers;
};

} // namespace rps::domain::util

#ifndef SCOPE_HELPER_HPP
#define SCOPE_HELPER_HPP

#include <type_traits>
#include <functional>

template <typename BeginFunction, typename EndFunction>
struct scope_helper
{
    template <typename F>
    struct is_invocable : std::is_constructible<std::function<void()>, 
    std::reference_wrapper<typename std::remove_reference<F>::type>> {};

    scope_helper(BeginFunction bf, EndFunction ef) : bf_(std::move(bf)), ef_(std::move(ef)) 
    { 
        static_assert(is_invocable<BeginFunction>::value && is_invocable<EndFunction>::value, 
        "Types are not invocable!"); 
        bf_(); 
    }

    ~scope_helper() { ef_(); }

private:
    BeginFunction bf_;
    EndFunction ef_;
};

#if __cplusplus > 201402L
template <typename BeginFunction, typename EndFunction>
scope_helper(BeginFunction, EndFunction) -> scope_helper<BeginFunction, EndFunction>;
#endif

template <typename BeginFunction, typename EndFunction>
scope_helper<BeginFunction, EndFunction> make_scope_helper(BeginFunction bf, EndFunction ef)
{
    return scope_helper<BeginFunction, EndFunction>(std::move(bf), std::move(ef));
}

#endif

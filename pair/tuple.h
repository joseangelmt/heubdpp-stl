#pragma once

namespace heubdpp
{
    template <typename _Ty1, typename _Ty2>
    struct pair
    {
        using first_type = _Ty1;
        using second_type = _Ty2;

        _Ty1 first{};
        _Ty2 second{};

        pair() = default;

        pair(_Ty1 const &v1, _Ty2 const &v2)
            : first{v1}, second{v2}
        {
        }

        pair(_Ty1 &&r1, _Ty2 &&r2)
            : first{std::move(r1)}, second{std::move(r2)}
        {
        }

        template <typename _Otro1 = _Ty1, typename _Otro2 = _Ty2>
        pair(_Otro1 const &v1, _Otro2 const &v2)
            : first(v1), second(v2)
        {
        }

        pair(pair const &) = default;

        template <typename _Otro1 = _Ty1, typename _Otro2 = _Ty2>
        pair(pair<_Otro1, _Otro2> const &p)
            : first(p.first), second(p.second)
        {
        }

        auto &operator=(pair const &otro) noexcept
        {
            first = otro.first;
            second = otro.second;
            return *this;
        }

        auto operator==(pair const &otro) const noexcept
        {
            return first == otro.first && second == otro.second;
        }

        auto operator!=(pair const &otro) const noexcept
        {
            return first != otro.first || second != otro.second;
        }

        auto operator<(pair const &otro) const noexcept
        {
            return first < otro.first ? true : second < otro.second;
        }

        auto operator<=(pair const &otro) const noexcept
        {
            return first <= otro.first ? true : second <= otro.second;
        }

        auto operator>(pair const &otro) const noexcept
        {
            return first > otro.first ? true : second > otro.second;
        }

        auto operator>=(pair const &otro) const noexcept
        {
            return first >= otro.first ? true : second >= otro.second;
        }
    };

    template <std::size_t Idx, typename _Ty1, typename _Ty2>
    constexpr auto &get(pair<_Ty1, _Ty2> &p)
    {
        static_assert(Idx < 2, "indice del par fuera de limites");

        if constexpr (Idx == 0)
            return p.first;
        else
            return p.second;
    }

    template <typename _Ty1, typename _Ty2>
    auto make_pair(_Ty1 const& v1, _Ty2 const& v2)
    {
        return pair<_Ty1, _Ty2>{v1, v2};
    }
}

#pragma once

#include <array>
#include <bit>
#include <string>
#include <string_view>
#include <type_traits>
#include <vector>

#if defined __clang__
#define IGUANA_INLINE __attribute__((always_inline)) inline
#define IGUANA__INLINE_LAMBDA __attribute__((always_inline)) constexpr
#elif defined _MSC_VER
#define IGUANA_INLINE __forceinline
#define IGUANA__INLINE_LAMBDA constexpr
#else
#define IGUANA_INLINE __attribute__((always_inline)) inline
#define IGUANA__INLINE_LAMBDA constexpr __attribute__((always_inline))
#endif

#if __has_cpp_attribute(likely) && __has_cpp_attribute(unlikely)
#define IGUANA_LIKELY [[likely]]
#define IGUANA_UNLIKELY [[unlikely]]
#else
#define IGUANA_LIKELY
#define IGUANA_UNLIKELY
#endif

#ifdef _MSC_VER

#if _MSC_VER >= 1920 && _MSVC_LANG >= 202002L
IGUANA_INLINE int countr_zero(unsigned long long x) {
  return std::countr_zero(x);
}
template <typename T>
constexpr inline bool contiguous_iterator = std::contiguous_iterator<T>;

#else
IGUANA_INLINE int countr_zero(unsigned long long x) {
  // x will never be zero in iguana
  unsigned long pos;
  _BitScanForward64(&pos, x);
  return pos;
}

namespace std {
template <typename T>
using remove_cvref_t =
    typename remove_cv<typename remove_reference<T>::type>::type;
}
template <typename T>
constexpr inline bool contiguous_iterator =
    std::is_same_v<std::remove_cvref_t<T>,
                   typename std::vector<char>::iterator> ||
    std::is_same_v<std::remove_cvref_t<T>,
                   typename std::vector<char>::const_iterator> ||
    std::is_same_v<std::remove_cvref_t<T>, typename std::string::iterator> ||
    std::is_same_v<std::remove_cvref_t<T>,
                   typename std::string::const_iterator> ||
    std::is_same_v<std::remove_cvref_t<T>, char *> ||
    std::is_same_v<std::remove_cvref_t<T>,
                   typename std::string_view::iterator> ||
    std::is_same_v<std::remove_cvref_t<T>,
                   typename std::string_view::const_iterator>;
#endif

#else

#if __cplusplus >= 202002L
IGUANA_INLINE int countr_zero(unsigned long long x) {
  return std::countr_zero(x);
}
template <typename T>
constexpr inline bool contiguous_iterator = std::contiguous_iterator<T>;
#else
IGUANA_INLINE int countr_zero(unsigned long long x) {
  // x will never be zero in iguana
  return __builtin_ctzll(x);
}
namespace std {
template <typename T>
using remove_cvref_t =
    typename remove_cv<typename remove_reference<T>::type>::type;
}
template <typename T>
constexpr inline bool contiguous_iterator =
    std::is_same_v<std::remove_cvref_t<T>,
                   typename std::vector<char>::iterator> ||
    std::is_same_v<std::remove_cvref_t<T>,
                   typename std::vector<char>::const_iterator> ||
    std::is_same_v<std::remove_cvref_t<T>, typename std::string::iterator> ||
    std::is_same_v<std::remove_cvref_t<T>,
                   typename std::string::const_iterator> ||
    std::is_same_v<std::remove_cvref_t<T>, char *> ||
    std::is_same_v<std::remove_cvref_t<T>,
                   typename std::string_view::iterator> ||
    std::is_same_v<std::remove_cvref_t<T>,
                   typename std::string_view::const_iterator>;
#endif

#endif

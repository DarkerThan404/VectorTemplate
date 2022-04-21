#include <iostream>

template <int ... Values>
struct static_vector
{};


template <typename Vector, int Added>
struct push_back
{};

template <int Added, int ... Values>
struct push_back<static_vector<Values ...>, Added>
{
    using type = static_vector<Values ..., Added>;
};


template <typename Vector, size_t Index>
struct at
{};

template <int Head, int ... Tail>
struct at<static_vector<Head, Tail ...>, 0>
{
    static constexpr auto value = Head;
};

template <size_t Index, int Head, int ... Tail>
struct at<static_vector<Head, Tail ...>, Index>
{
    static constexpr auto value = at<static_vector<Tail ...>, Index - 1>::value;
};

template<typename Vector, int Size, int Index>
struct expanding_vector
{};


template<int Size, int Index, int ... Values>
struct expanding_vector<static_vector< Values... >, Size, Index> {
    using type = typename expanding_vector<static_vector<Values ..., 0 >, Size - 1, Index - 1>::type;
};

template<int Index, int ... Values>
struct expanding_vector<static_vector< Values... >, 0, Index> {
    using type = static_vector<Values ... >;
};

template<int Size, int ... Values>
struct expanding_vector<static_vector< Values... >, Size, 0> {
    using type = typename expanding_vector<static_vector<Values ..., 1 >, Size - 1, - 1>::type;
};

template<typename TEnum, typename TPowers>
struct unit
{};

template<typename TEnum, TEnum index>
using basic_unit = unit < TEnum, typename expanding_vector < static_vector<>, static_cast<int>(TEnum::_count), (int)index>::type >;


template<typename LeftVector, typename RightVector, typename ResultVector>
struct sum 
{};


template<int Head1, int Head2, int ... Values1, int ... Values2, int ... Values3>
struct sum<static_vector<Head1, Values1 ...>, static_vector<Head2, Values2 ... >, static_vector< Values3 ...>>
{
private:
    static constexpr auto left_value = Head1;
    static constexpr auto right_value = Head2;
public:
    using type = typename sum<static_vector<Values1 ...>, static_vector<Values2 ... >, typename push_back<static_vector<Values3 ...>, static_cast<int>(left_value + right_value)>::type >::type;
};
#include <iostream>

template <int ... Values>
struct static_vector
{};

/// <summary>
/// expands vector to size and on index is 1
/// </summary>
/// <typeparam name="Vector"></typeparam>
template<typename Vector, int Size, int Index>
struct expand
{};

template<int Size, int Index, int ... Values>
struct expand<static_vector< Values... >, Size, Index> {
    using type = typename expand<static_vector<Values ..., 0 >, Size - 1, Index - 1>::type;
};

template<int Index, int ... Values>
struct expand<static_vector< Values... >, 0, Index> {
    using type = static_vector<Values ... >;
};

template<int Size, int ... Values>
struct expand<static_vector< Values... >, Size, 0> {
    using type = typename expand<static_vector<Values ..., 1 >, Size - 1, - 1>::type;
};

template<typename TEnum, typename TPowers>
struct unit
{};

template<typename TEnum, TEnum index>
using basic_unit = unit < TEnum, typename expand < static_vector<>, static_cast<int>(TEnum::_count), (int)index>::type >;


/// <summary>
/// Adds two vectors together and make them into a new one
/// </summary>
/// <typeparam name="LeftVector"></typeparam>
/// <typeparam name="RightVector"></typeparam>
template<typename LeftVector, typename RightVector>
struct add;

template<int ... LeftValues, int ... RightValues>
struct add<static_vector<LeftValues ...>, static_vector<RightValues ... >> {
    using type = static_vector<(LeftValues + RightValues) ... >;
};

/// <summary>
/// Substracts two vectors and make them into a new one
/// </summary>
/// <typeparam name="LeftVector"></typeparam>
/// <typeparam name="RightVector"></typeparam>
template<typename LeftVector, typename RightVector>
struct substract;

template<int ... LeftValues, int ... RightValues>
struct substract<static_vector<LeftValues ...>, static_vector<RightValues ... >> {
    using type = static_vector<(LeftValues - RightValues) ... >;
};

/// <summary>
/// Adds two vectors together and makes them into a new vector
/// </summary>
/// <typeparam name="LeftUnit"></typeparam>
/// <typeparam name="Rightunit"></typeparam>
template<typename LeftUnit, typename Rightunit>
struct unit_add {};

template<typename SameEnum, int ... Left, int ... Right>
struct unit_add < unit < SameEnum, static_vector<Left ...>>, unit < SameEnum, static_vector<Right ... >>>{
    using type = unit <
        SameEnum,
        typename add<
        static_vector<Left ... >,
        static_vector<Right ... >
        >::type
    >;
};

/// <summary>
/// Substracts two unit and makes them into a new unit
/// </summary>
/// <typeparam name="LeftUnit"></typeparam>
/// <typeparam name="Rightunit"></typeparam>
template<typename LeftUnit, typename Rightunit>
struct unit_substract {};

template<typename SameEnum, int ... Left, int ... Right>
struct unit_substract < unit < SameEnum, static_vector<Left ...>>, unit < SameEnum, static_vector<Right ... >>> {
    using type = unit <
        SameEnum,
        typename substract<
        static_vector<Left ... >,
        static_vector<Right ... >
        >::type
    >;
};

/// <summary>
/// Adds all vector of same system together
/// </summary>
/// <typeparam name="Head"></typeparam>
/// <typeparam name="...Tail"></typeparam>
template<typename Head, typename ... Tail>
struct add_all
{};

/// <summary>
/// Special case
/// </summary>
/// <typeparam name="SingleUnit"></typeparam>
template<typename SingleUnit>
struct add_all<SingleUnit>
{
    using type = SingleUnit;
};

/// <summary>
/// Zero case
/// </summary>
/// <typeparam name="LastLeft"></typeparam>
/// <typeparam name="LastRight"></typeparam>
template<typename LastLeft, typename LastRight>
struct add_all<LastLeft, LastRight>
{
    using type = typename unit_add<LastLeft, LastRight>::type;
};

/// <summary>
/// Adds first two units together and then result calls on itself
/// </summary>
/// <typeparam name="LeftUnit"></typeparam>
/// <typeparam name="RightUnit"></typeparam>
/// <typeparam name="...Tail"></typeparam>
template<typename LeftUnit, typename RightUnit, typename ... Tail>
struct add_all<LeftUnit, RightUnit, Tail ...> 
{
private:
    using SumHead = typename unit_add<LeftUnit, RightUnit>::type;
public:
    using type = typename add_all<SumHead, Tail ...>::type;
};


template <typename TFirstUnit, typename ... TOtherUnits>
using multiplied_unit = typename add_all<TFirstUnit, TOtherUnits ...>::type;

template <typename TDividendUnit, typename TDivisorUnit>
using divided_unit = typename unit_substract<TDividendUnit, TDivisorUnit>::type ;

template <typename TUnit, typename TValue = double>
struct quantity {
private:
    TValue value_;
public:
    explicit quantity(TValue value) : value_(value){}

    TValue value() { return value_; }
};

template<typename TEnum, typename TPowersLeft, typename TPowersRight>
auto operator * (quantity<unit<TEnum, TPowersLeft>> left, quantity<unit<TEnum, TPowersRight>> right) {
    auto LeftValue_ = left.value();
    auto RightValue_ = right.value();
    quantity < multiplied_unit<unit<TEnum, TPowersLeft>, unit<TEnum, TPowersRight>>> result(LeftValue_ * RightValue_);
    return result;
}

template<typename TEnum, typename TDividentPowers, typename TDivisorPowers>
auto operator / (quantity<unit<TEnum, TDividentPowers>> divident, quantity<unit<TEnum, TDivisorPowers>> divisor) {
    auto DividentValue_ = divident.value();
    auto DivisorValue_ = divisor.value();
    quantity < divided_unit<unit<TEnum, TDividentPowers>, unit<TEnum, TDivisorPowers>>> result(DividentValue_ / DivisorValue_);
    return result;
}

template<typename TUnit>
auto operator + (quantity<TUnit> LeftOperand, quantity<TUnit> RightOperand) {
    auto LeftOperand_ = LeftOperand.value();
    auto RightOperand_ = RightOperand.value();
    quantity < TUnit> result(LeftOperand_ + RightOperand_);
    return result;
}

template<typename TUnit>
auto operator - (quantity<TUnit> LeftOperand, quantity<TUnit> RightOperand) {
    auto LeftOperand_ = LeftOperand.value();
    auto RightOperand_ = RightOperand.value();
    quantity < TUnit> result(LeftOperand_ - RightOperand_);
    return result;
}
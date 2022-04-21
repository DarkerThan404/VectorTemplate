#include <iostream>

template <int ... Values>
struct static_vector
{};


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



template<typename LeftVector, typename RightVector>
struct add;

template<int ... LeftValues, int ... RightValues>
struct add<static_vector<LeftValues ...>, static_vector<RightValues ... >> {
    using type = static_vector<(LeftValues + RightValues) ... >;
};

template<typename LeftVector, typename RightVector>
struct substract;

template<int ... LeftValues, int ... RightValues>
struct substract<static_vector<LeftValues ...>, static_vector<RightValues ... >> {
    using type = static_vector<(LeftValues - RightValues) ... >;
};

template<typename LeftUnit, typename Rightunit>
struct unit_add {};

template<typename SameEnum, int ... Left, int ... Right>
struct unit_add < unit < SameEnum, static_vector<Left ...>>, unit < SameEnum, static_vector<Right ... >>>{
    //using type = unit < SameEnum, typename added<static_vector<Left ...>, static_vector<Right ...>>::type>>;
    using type = unit <
        SameEnum,
        typename add<
        static_vector<Left ... >,
        static_vector<Right ... >
        >::type
    >;
};

template<typename LeftUnit, typename Rightunit>
struct unit_substract {};

/*template<typename Enum,typename TPowers, typename OtherEnum, typename OtherTPowers>
struct unit_substract<unit<Enum, TPowers>, unit<OtherEnum, OtherTPowers>> {
    using type = static_vector<>;
};*/

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
template<typename Head, typename ... Tail>
struct add_all
{};

template<typename SingleUnit>
struct add_all<SingleUnit>
{
    using type = SingleUnit;
};
template<typename LastLeft, typename LastRight>
struct add_all<LastLeft, LastRight>
{
    using type = typename unit_add<LastLeft, LastRight>::type;
};

template<typename LeftUnit, typename RightUnit, typename ... Tail>
struct add_all<LeftUnit, RightUnit, Tail ...> 
{
private:
    using SumHead = typename unit_add<LeftUnit, RightUnit>::type;
public:
    using type = typename add_all<SumHead, Tail ...>::type;
};

template<typename TDivident, typename TDivisor>
struct divide{};

template<typename SameUnit, int ... Divident , int ... Divisor>
struct divide<unit<SameUnit, static_vector<Divident ... >>, unit<SameUnit, static_vector<Divisor ... >>> {
    using type = typename substract<unit<SameUnit, static_vector<Divident ... >>, unit<SameUnit, static_vector<Divisor ... >>>::type;
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
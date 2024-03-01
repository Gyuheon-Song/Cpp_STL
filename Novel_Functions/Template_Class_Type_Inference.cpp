# include <iostream>


template <typename T1, typename T2, typename T3>
class My_Wrapper {
    T1 t1;
    T2 t2;
    T3 t3;

public:
    explicit My_Wrapper(T1 t1_, T2 t2_, T3 t3_)   // 생성자
        : t1{t1_}, t2{t2_}, t3{t3_}
    {}

};

// C++17 이전에 사용하던 헬퍼 함수
template <typename T1, typename T2, typename T3>
My_Wrapper<T1, T2, T3> Make_Wrapper(T1 t1_, T2 t2_, T3 t3_) {
    return { t1_, t2_, t3_ };
}

template <typename T>
struct Sum {
    T value;      // value라는 멤버

    template<typename ... Ts>   // 함수 템플릿
    Sum(Ts&& ... values) : value{(values + ...)}{}  // Sum이라는 함수 호출이 일어나면 value라는 멤버를 Sum의 인자들의 합으로 초기화
};

template<typename ... Ts>
Sum(Ts&& ... ts) -> Sum < std::common_type_t<Ts...>>;  // 인스터스화 시킬 때 Sum에 인자로 넣어주는 변수의 자료형을 common_type_t 특성값을 활용하여 추론하라


int main() {

    // 한번에 특수화 및 인스턴스 생성 가능
    std::pair my_pair(123, "abc"); // std::pair<int, const char*>
    std::tuple my_tuple(123, 12.3, "abc"); // std::tuple<int, double, const char*>

    // before C++17
    My_Wrapper<int, double, const char*> wrapper{ 123, 12.3, "abc" };
    
    auto wrapper(Make_Wrapper(123, 12.3, "abd"));  // 헬퍼함수의 도움을 받았었다


    // after C++17
    My_Wrapper wrapper{ 123, 12.3, "abc" };

    Sum s           { 1u, 2.0, 3, 4.0f };   // unsigned, double, int float으로 인스턴스화  ->  common_type_t가 double형을 기본 자료형으로 반환
    Sum str_sum     { std::string{"abc"}, "def" };   // string 클래스와 char[4]로 인스턴스화 -> common_type_t가 추론 가이드에 따라 std::string 자료형으로 반환

    std::cout << s.value << '\n'      // 10
        << str_sum.value << '\n';     // abcdef

    return 0;
}
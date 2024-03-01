# include <iostream>
# include <vector>


/*++++++++++++++++++++++++++++ Before C++17 +++++++++++++++++++++++++++++++++++++++*/
template<typename T>
class Past_Addable
{
    T value;

public:
    Past_Addable(T v)
        :val{v}
    {

    }

    // std::enable_if_t<condition, type>은 조건식이 참인 경우 타입을 평가한다
    // 두 번쩨의 add 함수에서 같은 조건을 반대로 사용함으로써 두 개의 구현 중 하나만 true가 될 수 있다. 그럼에도 이러한 구현을 오류가 아니다
    // SFINAE; Substitution Failure Is Not An Error 원칙에 의해 밑의 두 개의 구현 중 하나에서 잘못된 템플릿 표현식으로 인해 반환값이 잘못되더라도 오류가 발생되는 것이 아닌 단순히 다른 함수 구현을 시도해 볼 것이다
    template<typename U>
    std::enable_if_t<!std::is_same<T, std::vector<U>>::value, T>
        add(U x) const
    {
        return val + x;
    }

    template<typename U>
    std::enable_if_t<std::is_same<T, std::vector<U>>::value, std::vector<U>>
        add(U x) const {
        auto copy(val);
        for (auto& n : copy) {
            n += x;
        }
        return copy;
    }

};


/*++++++++++++++++++++++++++++ After C++17 ++++++++++++++++++++++++++++++++++++++*/
template<typename T>
class Addable
{
    T val;

public:
    Addable(T v)    // 생성자 오버로딩
        : val{v}    // T 클래스의 val 변수를 v로 중괄호 초기화
    {

    }

    template<typename U>
    T add(U x) const     // T 클래스를 반환하는 add 함수 템플릿 -> const키워드로 인해 이 함수는 객체의 멤버변수를 수정할 수 없다
    {
        // std::is_same<A, B>의 경우 A와 B가 같은 type인지 여부를 Boolean값으로 반환한다
        // 여기서 사용된 constexpr-if의 조건식은 std::is_same<T, std::vector<U>>::value 이다
        // T를 std::vector<X>로 특수화 시 true값으로 평가하고 U를 X타입의 매개변수로 하여 add함수를 호출한다
        if constexpr (std::is_same_v<T, std::vector<U>>) { // 만약 T와 std::vector<U>가 동일한 경우에는 벡터의 각 요소에 해당 값을 더해야 한다
            auto copy(val);    // 벡터의 사본 구하기
            for (auto &n : copy) {   // 벡터의 보든 요소에 해당 값 더하기
                n += x;
            }
            return copy;
        }
        else {   // 벡터가 아닌 경우는 그냥 더한다
            return val + x;
        }
    }
};


int main() {

    Addable<int>{1}.add(2);                 // 3
    Addable<float>{1.0}.add(2);             // 3.0
    Addable<std::string>{"aa"}.add("bb");   // aabb

    std::vector<int> v{ 1, 2, 3 };
    Addable<std::vector<int>>{v}.add(10);   // v의 각 요소에 10을 더하면 std::vector<int>{11, 12, 13} 가 된다

    std::vector<std::string> sv{ "a", "b", "c"};
    Addable<std::vector<std::string>>{sv}.add(std::string{ "z" });  // sv의 각 요소에 std::string{"z"}를 더하면 std::Vector<std::string>>{"az", "bz", "cz"}가 된다


    // constexpr-if는 일반적으로 if-else와 하는 일이 동일하지만 검사하는 조건이 컴파일 타임에 평가되어야 한다
    // 컴파일러가 생성한 런타임 코드는 constexpr-if 조건 분기 명령을 포함하지 않는다
    // 모든 constexpr-if분기 명령은 문법에 맞아야 하지만 그렇지 않은 분기 명령은 의미상 유효할 필요는 없다
    // 하나의 constexpr-if-else 블록에 여러개의 조건이 있을 수 있다
    if constexpr (a) {
        // 작업 수행
    }
    else if constexpr (b) {
        // 다른 작업 수행
    }
    else {
        // 아예 다른 작업 수행
    }

    return 0;
}
# include <iostream>
# include <vector>
# include <set>


template<typename ... Ts>    // Signature를 먼저 정의한다(함수 템플릿)
auto Sum(Ts ... ts);         // Sum의 인자는 Ts 타입의 인자들인 매개변수 ts가 된다

template<typename ... Ts>  // Sum 함수 구현 
auto Sum(Ts ... ts)
{   // 왼쪽 단항 접기 실행
    return (ts + ... + 0);   // ts와 +와 ...를 통해 모든 인자를 펼쳐서 연산을 수행한다 -> Folding
    // 만약 Sum()이 호출되어 가변 parameter 묶음에 접힐 수 있는 값이 포함되지 않은 경우 오류발생 방지 및 빈 합계를 0으로 특정할 수 있도록 + 0 을 해주어 식별값을 0으로 해준다
}

// Folding을 지원하는 연산자
// +, -, *, /, %, ^, |, =, &, <, >, <<, >>, +=, -=, *=, /=, %=, ^=, &=, |=, <<=, >>=, ==, !=, <=, >=, &&, ||, ,, .*, ->*

template<typename ... Ts>
auto Product(Ts ... ts)
{
    return (ts * ... * 1);   // 여기서 수행하는 곱셈에서의 식별값은 1로 했다 -> 인자가 들어오지 않는 경우 1을 반환
}

// && 와 || 간은 경우 내장된 자체 식별자를 가진다
// &&의 경우 식별자 true
// ||의 경우 식별자 false


template<typename R, typename ... Ts>
auto Matches(const R& range, Ts ... ts)  // Helper Function
{
    // std::count는 세개의 인자를 받는다 -> 반복 가능한 범위의 시작 iterator, 반복 가능한 범위의 끝 iterator, 개수를 셀 값
    return (std::count(std::begin(range), std::end(range), ts) + ...);
    // Fold Expression을 통해 count()함수는 ts의 범위에 있는 모든 요소의 개수를 반환한다
    // Fold Expression을 통해 위 구현에서는 count()함수는 같은 range의 시작과 끝 iterator를 전달하며 세번째 인자만 다른 parameter를 전달한다

    // std::list, std::array, std::set, std::initializer_list등의 인스턴스에서 동일하게 동작
}


// set에 삽입
// set의 삽입함수가 가지는 signature : std::pair<iterator, bool> insert(const value_type& value)
// insert함수는 iterator와 bool을 반환한다 -> 삽입 성공 시 true와 함께 set에 추가된 새로운 요소를 iterator가 가리킨다
                                        //  삽입 실패 시 false와 함께 삽입하려하는 값과 충돌되는 기존 요소를 iterator가 가리킨다
template <typename T, typename ... Ts>
bool Insert_All(T& set, Ts ... ts)   // helper function
{
    // 아이템을 삽입한 후 second에 접근 = bool값
    // fold expression으로 && 연산자 사용하여 모든 삽입이 성공했는지 여부 판단
    // 인자들 중 중간에 어떤 요소가 삽입 실패 할 경우 다른 요소의 삽입도 중지하게 된다
    return (set.insert(ts).second && ...);
}


// 어떤 범위에 여러 변수들이 다 속하는지 검사
template <typename T, typename ... Ts>
bool Within(T min, T max, Ts ... ts)
{
    return ((min <= ts && ts <= max) && ...);  // 모든 변수들이 min과 max 사이에 존재하는지 && 연산으로 오른쪽 접기
}


/*+++++++++++++++++++++ vector에 여러개의 요소 넣기 +++++++++++++++++++++++++++*/
template <typename T, typename ... Ts>
void InsertAll(std::vector<T>& vec, Ts ... ts)
{
    (vec.push_back(ts), ...);   //  , 를 사용함으로써 결과값에 표현식 접기를 쓰는 것이 아닌 개별 vec.push_back(...)으로 parameter묶음을 펼친다
}                               // , 는 암시적인 식별 값 void()를 가지고 있기에 인자가 만약 없어도 잘 작동한다


int main() {

    // ... + ts
    // 1 + (2 + (3 + (4 + 5)))  : 왼쪽 단항접기 -> 왼쪽으로 접어간다
    
    // ts + ...  
    // (((1 + 2) + 3) + 4) + 5  : 오른쪽 단항접기 -> 오른쪽으로 접어간다

    //초깃값을 통해 접는 것은 Binary Fold라고 한다
    // ts + ... + 0  오른쪽 단항 Binary Fold
    // 0 + ... + ts  왼쪽 단항 Binary Fold

    int the_sum{ Sum(1, 2, 3, 4, 5) };      // the_sum 값 : 15

    std::string a{ "Hello " };
    std::string b{ "World" };
    std::cout << Sum(a, b) << '\n';   // Hello World


    std::vector<int> v{ 1, 2, 3, 4, 5 };

    Matches(v, 2, 5);       // v 벡터 안에 2는 1개 5도 1개 이므로 1+1 = 2 반환
    Matches(v, 100, 200);    // 0 반환
    Matches("abcdefg", 'x', 'y', 'z');  // 0 반환
    Matches("abcdefg", 'a', 'd', 'f');  // 3 반환


    /*++++++++++++++ set에 여러개의 삽입 성공 여부 확인 ++++++++++++++++++++++++*/
    std::set<int> my_set{ 1, 2, 3 };
    Insert_All(my_set, 4, 5, 6);        // true
    Insert_All(my_set, 7, 8, 2);        // 2 값의 충돌로 false

    std::set<int> my_set{ 1, 2, 3 };
    Insert_All(my_set, 4, 2, 5);        // 2 를 삽입하면서 false를 반환한다 -> 5를 삽입하는 작업은 수행되지 않는다
    // my_set은 {1, 2, 3, 4}의 상태이다
    

    /*++++++++++++++++++++ 모든 변수들이 어떤 범위에 들어있는지 검사 +++++++++++++++++++++++++++++*/
    Within(10, 20, 1, 15, 30);   // 30은 10과 20사이의 수가 아니므로 false 반환
    Within(10, 20, 11, 12, 13);  // 모든 수가 10과 20 사이의 수이므로 true 반환
    Within(5.0, 5.5, 5.1, 5.2, 5.3);   // true 반환

    // std::string 클래스를 사용하면 사전순 범위 안에 속하는지 여부 검사 가능
    std::string aaa{ "aaa" };
    std::string bcd{ "bcd" };
    std::string def{ "def" };
    std::string zzz{ "zzz" };
    Within(aaa, zzz, bcd, def);   // true
    Within(aaa, def, bcd, zzz);   // false


    /* +++++++++++++++++++++ vector에 여러개의 요소를 넣는 헬퍼함수 +++++++++++++++++++++++++++++++*/
    std::vector<int> vv{ 1, 2, 3 };
    InsertAll(vv, 4, 5, 6);    // vv{1, 2, 3, 4, 5, 6}
    InsertAll(vv);             // vv{1, 2, 3, 4, 5, 6}  인자가 없어도 작동할 수 있도록 헬퍼 함수를 구현해 놓았다

    return 0;
}
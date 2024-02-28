# include <iostream>
# include <tuple>
# include <chrono>
# include <string>
# include <vector>
# include <map>

std::pair<int, int> Divide_remainder(int _dend, int _divi) {  // 나머지와 몫을 pair로 반환하는 함수
    int fraction = _dend / _divi;
    int remainder = _dend % _divi;
    return { fraction, remainder };
}


std::tuple<std::string, std::chrono::system_clock::time_point, unsigned> Stock_info(const std::string& name) {
    std::chrono::system_clock::time_point valid_time = std::chrono::system_clock::now();
    unsigned price = 800; 
    return std::make_tuple(name, valid_time, price);
}

struct employee {  // 직원 정보 구조체
    unsigned id;
    std::string name;
    std::string role;
    unsigned salary;
};

int main() {

    /*+++++++++++ C++17 이전의 Unpacking ++++++++++++*/

    std::pair<int, int> Divide_remainder(int dividend, int divisor);   // 몫과 나머지를 pair로 반환하는 함수

    // pair변수의 각 값에 접근
    const std::pair<int, int> result = Divide_remainder(16, 3);
    std::cout << "16 / 3 is "
        << result.first << "with a remainder of "
        << result.second << '\n';


    /*++++++++++++ C++17 이후의 Unpacking ++++++++++++*/
    auto [fraction, remainder] = Divide_remainder(16, 3);
    std::cout << "16 / 3 is "
        << fraction << " with a remainder of "
        << remainder << '\n';


    /*++++++++++++++++++++++ tuple에서의 Structured Binding +++++++++++++++++++++*/
    // 온라인 주식 정보를 구하는 함수
    std::tuple<std::string, std::chrono::system_clock::time_point, unsigned> Stock_info(const std::string & name);

    // 이름, 거래 시간, 가격을 Unpacking
    const auto [name, valid_time, price] = Stock_info("NVIDIA");


        /*++++++++++++++++++++++ 구조체에서의 Structured Binding +++++++++++++++++++++*/
    std::vector<employee> employees;

    for (const auto &[id, name, role, salary] : employees) {
        std::cout << "Name: " << name
            << "Role: " << role
            << "Salary: " << salary << '\n';
    }


    /*++++++++++++++++++++ Structured Binding의 패턴 ++++++++++++++++++*/

    //  auto [var1, var2, var3, ...] = <pair, tuple, map, struct 또는 array 표현식>
    // unpacking하는 변수들은 할당된 표현식(자료구조)에 포함되는 변수의 개수와 일치해야 한다 -> 다른 경우 컴파일 에러
    // unpacking가능한 자료형
    //  1. std::pair
    //  2. std::tuple
    //  3. struct
    //      - 모든 멤버변수는 비정적이며 동일한 기본 클래스에서 정의되어야 한다
    //      - 멤버 변수를 정의한 순서에 따라 unpacking된다
    //  4. 정적배열
    // 자료형은 auto, const auto, const auto&, auto&&, ... 가 될 수 있다

    /*++++++++++++++++ C++17 +++++++++++++++++++++++++++*/
    std::map<std::string, size_t> animal_population{
        {"camels", 36542600},
        {"sheep", 1064500000}
    };
    animal_population.insert({ "humans", 7000000000 });
    animal_population.insert({ "chickens", 1127364500000 });
    
    // std::map 컨테이너를 순회하면서 std::pair<const key_type, value_type> 노드를 통해 동작
    for (const auto& [species, count] : animal_population) {
        std::cout << "There are " << count << ' ' << species
            << " on this planet.\n";
    }

    /*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
    // C++17 이전에서의 std::tie를 통해 구조체 형태 바인딩 유사 동작
    // std::ignore를 통해 필요없는 값은 더미변수 처리를 할 수 있는 강점이 있다
    int remainder;
    std::tie(std::ignore, remainder) = Divide_remainder(16, 5);
    std::cout << "16 % 5 is " << remainder << '\n';



    /*++++++++++++++++++++++ RVO; Return Value Optimization +++++++++++++++++++*/
    // 최근 컴파일러에서는 함수가 복잡한 구조체를 반환하더라도 중간 복사 과정(반환되는 함수 내에서 객체 초기화 후 호출하는 쪽의 변수에 복사)을 생략한다

    return 0;
}
# include <iostream>
# include <vector>

int main() {

    /* ++++++++++++++++++++++ auto 자료형의 추론 없이 중괄호 초기화 +++++++++++++++++++++++++*/

    // int를 초기화하는 세가지 동일한 방법
    int x1 = 1; 
    int x2(1);
    int x3{ 1 };

    // vector 초기화
    std::vector<int> v1 = { 1, 2, 3 }; // 1, 2, 3 세개의 int값을 가지는 벡터
    std::vector<int> v2(10, 20);   // 10개의 int값 20을 가지는 벡터
    std::vector<int> v3{ 1, 2, 3 }; // 1, 2, 3 세개의 int값을 가지는 벡터

    // auto 자료형의 추론으로 중괄호 초기화
    auto v{ 1 };  // v는 int 1
    auto x{ 1, 2 };  // error : 중괄호 초기화 시에는 중괄호 안에 단일 요소만 가능
    auto x = { 1 }; // x는 std::initializer_list<int> {1}
    auto y = { 1, 2 }; // y는 std::initializer_list<int> {1, 2}
    auto z = { 1, 2, 3.0 };  // 자료형 추론 불가

    // 배열이나 클래스, 구조체 등의 집합체 경우 중괄호 초기화를 하게 되면
    // std::initializer_list<type> 생성자와 일치하게 되면서 초기화가 가능하다

    // 반면, 비집합체인 경우 목록으로 초기화가 불가할 뿐더러, auto를 사용하는 경우에는 단일 요소만 중괄호 초기화가 가능하다


    // ()생성자와 {}생성자의 비교
    // ()의 경우 가장 적절한 생성자를 찾고 암시적 형변환 발생
    int x(1.2);   // int x에 1이 저장된다
    // {}의 경우 적절한 생성자를 선택하기만 할 뿐 암시적 형변환이 일어나지 않는다
    int x{ 1.2 }; // 컴파일 불가


    auto var_name{ one_element }; // one_element와 같은 자료형이 되도록 auto 추론
    auto var_name{ element1, element2, ... };  // 컴파일 불가
    auto var_name = { element1, element2, element3,... };  // 목록의 모든 요소가 같은 자료형이 되도록 std::initializer_list<자료형> 추론
    
    return 0;
}
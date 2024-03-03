# include <iostream>
# include <vector>
# include <algorithm>

using namespace std;


// Predicate 함수 : 해당 값이 조건에 개해 잠인지 거짓인지 판별하는 함수
//  람다식 :   
// ++++++ remove_if()의 세번째 인자로 바로 구현하는 경우 ++++++++++++++++
//            [capture list] (받을 인자) -> type {return 조건식;}
//            [capture list] (받을 인자) {return 조건식;}
// ++++++ 따로 함수 객체를 구현하는 경우 ++++++++++++++++++++++++++++++++++
//            auto func = [capture list] (받을 인자) {return 조건식;};
//            auto func([capture list] (받을 인자) {return 조건식;});

const auto Odd([](int i) {   // 외부변수를 캡쳐하지 않을 것이므로 []를 비워놓고
    return i % 2 != 0;
    });

int main() {

    vector<int> v{ 1, 2, 3, 2, 5, 2, 6, 2, 4, 8 };

    const auto new_end (remove(v.begin(), v.end(), 2));  // remove함수는 지정한 값과 일치하는 값의 자리에 다른 원소들을 앞으로 땡겨와서, 줄어들고 남은 요소들의 마지막 요소의 다음위치을 반환한다
    v.erase(new_end, v.end());  // 벡터가 차지하고 있었던 메모리는 그대로이지만 요소는 줄어들었으므로 erase로 new_end부터 벡터의 끝까지에 들어있는 의미없는 값을 실질적으로 지워준다 

    for (auto i : v) {
        cout << i << ", ";
    }
    cout << '\n';    // 1, 3, 5, 6, 4, 8

    // Predicate함수를 정의하고 remove_if()와 함께 사용하여 remove_if()가 어떤 iterator를 반환하든 erase()함수 내에서 사용할 때 매우 안전
    // remove_if()가 어떤 것도 삭제하지 않을 때 end()를 반환하여 erase(end(), end())가 되어 아무 일도 일어나지 않는다
    v.erase(remove_if(begin(v), end(v), Odd), end(v));   // 한번에 조건에 부합하는 원소를 실질적으로 지우고 벡터의 크기를 줄이는 작업 (하지만 벡터에 실질적으로 할당된 메모리는 그대로이다)
    v.shrink_to_fit(); // 정확히 필요한 새로운 메모리 공간만 벡터에 할당하고 전체 요소를 복사하여 옮겨넣어 이전의 벡터가 할당되었었던 메모리 공간 해제

    for (auto i : v) {
        cout << i << ", ";
    }
    cout << '\n';    // 6, 4, 8


    /*++++++++++++++*/
    // std::remove()의 경우에는 다른 container에도 사용 가능하나, erase()의 경우는 동적인 container에서는 지원하지 않음
    // 동적 배열에서 std::remove()를 사용하는 경우 새로운 end iterator다음의 값을 '\n'으로 겹쳐 쓸 수 있다

    return 0;
}
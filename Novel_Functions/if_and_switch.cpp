# include <iostream>
# include <map>
# include <mutex>
# include <memory>
# include <Windows.h>

void Move_left() {};
void Move_back() {};
void Move_fwd() {};
void Move_right() {};
void Quit_game() {};
void Select_tool(const char c) {};

int main() {
    
    std::map<char, char> character_map;

    /*++++++++++++++++++++++++ if statement with initializer +++++++++++++++++*/
    // if구문과 std::map의 find()함수를 사용하여 특정 문자를 찾는 경우
    // if statement with initializer를 사용가능
    // if문이 실행될 때만 유효한 변수 itr를 선언 -> itr의 scope가 if문의 중괄호 안으로 제한된다
    // 초기화 선언과 조건문은 ;로 구분한다
    if (auto itr(character_map.find('c')); itr != character_map.end()) {
        // *itr이 유효한 경우 작업 수행
    }
    else {
        // itr이 end iterator이므로 참조하지 않는다
    }
    // if-else 바깥에서는 itr은 더이상 사용할 수 없다


    /*++++++++++++++++++++++++ switch statement with initializer ++++++++++++++++++++++++++*/
    // 키 입력문자를 구하는 동시에 switch문으로 값을 확인하여 게임제어

    switch (char c(getchar()); c) {  // 문자를 입력받아 바로 입력받은 값으로 변수 c를 초기화
        case 'a': Move_left(); break;
        case 's': Move_back(); break;
        case 'w': Move_fwd(); break;
        case 'd': Move_right(); break;
        case 'q': Quit_game(); break;

        case '0': Select_tool('0'); break;
        default:
            std::cout << "invalid input: " << c << '\n';
    }


    /*+++++++++++++++++++++++++ if문의 초기화를 통한 변수영역 제어 syntax sugar 전후 비교 ++++++++++++++++++*/
    // before C++17
    {
        auto var(init_value);
        if (condition) {
            // A condition -> var에 접근 가능
        }
        else {
            // B condition -> var에 접근가능
        }
        // if-else의 영역 외부에서도 var에 접근 가능
    }

    // after C++17
    {
        if (auto var(init_value); condition) {
            // A condition -> var에 접근 가능
        }
        else {
            // B condition -> var에 접근 가능
        }
        // if statement with initializer에 의해서 if-else 영역 외부에서는 var에 접근 불가
    }


    /*++++++++++++++ switch문의 초기화를 통한 변수 영역 제어 syntax sugar 전후 비교 ++++++++++++++++++*/
    // before C++17
    {
        auto var(init_value);
        switch (var) {
        case 1:...; //
        case 2:...;//
            // ...
        }
        // switch-case문 외부에서도 var에 접근 가능
    }

    // after C++17
    {
        switch (auto var(init_value); var) {
        case 1:...;//
        case 2:...;//
            //...
        }
        //switch-case문 외부에서는 var에 접근 불가
    }


    /*+++++++++++++++++++++++++ Mutex Lock ++++++++++++++++++++++++++++++++ */
    // mutex-lock을 활용한 multi-thread 환경에서의 동기화 달성
    // std::lock_guard는 락 가드 패턴을 쉽게 사용할 수 있도록 도와주는 클래스. lock_guard 클래스의 인스턴스는 생성될 때 락을 얻고, 소멸될 때 락을 해제
    // 락의 스코프 범위를 제한하고 락을 해제하는 것을 잊어버리는 실수를 방지.
    // 잠금장치의 의미를 가진 std::mutex 클래스 객체를 생성하고 초기화
    // my_mutex를 락으로 사용하여 some_condition이 참인 경우에 한정된 범위 내에서 락을 유지
    // 락을 명시적으로 해제하지 않아도 std::lock_guard의 소멸자가 락을 자동으로 해제.
    if (std::lock_guard<std::mutex> lg{ my_mutex }; some_condition) {
        // lock_guard의 생성자가 std::mutex 클래스인 my_mutex 장금

        // 작업 수행

        // lock_guard의 소멸자가 my_mutex 잠금 해제
    }


    /*+++++++++++++++++++++++++++ weak pointer ++++++++++++++++++++++++++++++++*/
    std::weak_ptr<int> weak_pointer = std::make_shared<int>(42);
    if (auto shared_pointer(weak_pointer.lock()); shared_pointer != nullptr) {
        // shared 객체가 계속 존재
    }
    else {
        // shared_pointer 변수에 접근은 가능하나 nullptr이다
    }
    // shared_pointer 변수에 접근 불가


    /*++++++++++++++++++++++++++ exit code 반환하는 window의 kernel API function +++++++++++++++++++++++++++*/
    // 주어진 핸들이 유용한 경우에만 해당 프로세스 핸들의 exit 코드를 반환
    if (DWORD exit_code; GetExitCodeProcess(process_handle, &exit_code)) {

        std::cout << "Exit code of process was: " << exit_code << '\n';
    }
        // if 조건문 외부에서는 exit_code 변수가 사용되지 않는다
    ㅊ
    return 0;
}
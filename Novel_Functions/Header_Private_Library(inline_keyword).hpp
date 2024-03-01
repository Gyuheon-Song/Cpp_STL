# include <iostream>

// 기존에 함수 inline만 가능했던 반면 이제 변수 inline도 가능하다

/*+++++++++++++++++++ Before C++17 ++++++++++++++++++++++++++++++*/
// 여러개의 모듈에 헤더가 include되어도 어디서든 같은 인스턴스에 접근 가능
// 그러나 해당 객체는 프로그램의 시작이 아닌 첫 함수 호출 시에만 생성되기에 함수 호출 이전에 필요한 작업이 있는 경우에는 사용할 수 없다
// 해결책으로는 클래스 템플릿을 만드는 방법이 있다
class Foo
{
public:
    static std::string& standard_string()  // static 객체의 reference를 반환하는 static함수
    {
        static std::string s{ "some standard string" };
        return s;
    }
};


/* ++++++++++++++++++++++++++++++++ After C++17 +++++++++++++++++++++++++++++++++++*/

class Process_Monitor
{
public:
    static const inline std::string standard_string   // inline 키워드를 통해 링커는 동일한 signature로 된 여러 개의 같은 symbol을 찾은 경우
        { "some static globally available string" };  // 첫 번째 심볼을 선택하고 다른 심볼도 같은 정의를 가지고 있다고 신뢰한다
};

inline Process_Monitor global_process_monitor;

// 위와같은 헤더파일을 inline 키워드 없이 구현해 놓을 경우 이 헤더파일을 include한 모든 모듈에서 Process_Monitor::standard_string와 global_process_monitor 심볼을 찾을 것이다
// 이로 인해 ODR; One Definition Rule 충돌이 발생한다
// 두 개의 같은 inline 심볼을 정의하게 되면 첫 번째 등장하는 심볼만 허용하고 나머지 심볼은 버린다
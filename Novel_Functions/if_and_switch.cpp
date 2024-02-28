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
    // if������ std::map�� find()�Լ��� ����Ͽ� Ư�� ���ڸ� ã�� ���
    // if statement with initializer�� ��밡��
    // if���� ����� ���� ��ȿ�� ���� itr�� ���� -> itr�� scope�� if���� �߰�ȣ ������ ���ѵȴ�
    // �ʱ�ȭ ����� ���ǹ��� ;�� �����Ѵ�
    if (auto itr(character_map.find('c')); itr != character_map.end()) {
        // *itr�� ��ȿ�� ��� �۾� ����
    }
    else {
        // itr�� end iterator�̹Ƿ� �������� �ʴ´�
    }
    // if-else �ٱ������� itr�� ���̻� ����� �� ����


    /*++++++++++++++++++++++++ switch statement with initializer ++++++++++++++++++++++++++*/
    // Ű �Է¹��ڸ� ���ϴ� ���ÿ� switch������ ���� Ȯ���Ͽ� ��������

    switch (char c(getchar()); c) {  // ���ڸ� �Է¹޾� �ٷ� �Է¹��� ������ ���� c�� �ʱ�ȭ
        case 'a': Move_left(); break;
        case 's': Move_back(); break;
        case 'w': Move_fwd(); break;
        case 'd': Move_right(); break;
        case 'q': Quit_game(); break;

        case '0': Select_tool('0'); break;
        default:
            std::cout << "invalid input: " << c << '\n';
    }


    /*+++++++++++++++++++++++++ if���� �ʱ�ȭ�� ���� �������� ���� syntax sugar ���� �� ++++++++++++++++++*/
    // before C++17
    {
        auto var(init_value);
        if (condition) {
            // A condition -> var�� ���� ����
        }
        else {
            // B condition -> var�� ���ٰ���
        }
        // if-else�� ���� �ܺο����� var�� ���� ����
    }

    // after C++17
    {
        if (auto var(init_value); condition) {
            // A condition -> var�� ���� ����
        }
        else {
            // B condition -> var�� ���� ����
        }
        // if statement with initializer�� ���ؼ� if-else ���� �ܺο����� var�� ���� �Ұ�
    }


    /*++++++++++++++ switch���� �ʱ�ȭ�� ���� ���� ���� ���� syntax sugar ���� �� ++++++++++++++++++*/
    // before C++17
    {
        auto var(init_value);
        switch (var) {
        case 1:...; //
        case 2:...;//
            // ...
        }
        // switch-case�� �ܺο����� var�� ���� ����
    }

    // after C++17
    {
        switch (auto var(init_value); var) {
        case 1:...;//
        case 2:...;//
            //...
        }
        //switch-case�� �ܺο����� var�� ���� �Ұ�
    }


    /*+++++++++++++++++++++++++ Mutex Lock ++++++++++++++++++++++++++++++++ */
    // mutex-lock�� Ȱ���� multi-thread ȯ�濡���� ����ȭ �޼�
    // std::lock_guard�� �� ���� ������ ���� ����� �� �ֵ��� �����ִ� Ŭ����. lock_guard Ŭ������ �ν��Ͻ��� ������ �� ���� ���, �Ҹ�� �� ���� ����
    // ���� ������ ������ �����ϰ� ���� �����ϴ� ���� �ؾ������ �Ǽ��� ����.
    // �����ġ�� �ǹ̸� ���� std::mutex Ŭ���� ��ü�� �����ϰ� �ʱ�ȭ
    // my_mutex�� ������ ����Ͽ� some_condition�� ���� ��쿡 ������ ���� ������ ���� ����
    // ���� ��������� �������� �ʾƵ� std::lock_guard�� �Ҹ��ڰ� ���� �ڵ����� ����.
    if (std::lock_guard<std::mutex> lg{ my_mutex }; some_condition) {
        // lock_guard�� �����ڰ� std::mutex Ŭ������ my_mutex ���

        // �۾� ����

        // lock_guard�� �Ҹ��ڰ� my_mutex ��� ����
    }


    /*+++++++++++++++++++++++++++ weak pointer ++++++++++++++++++++++++++++++++*/
    std::weak_ptr<int> weak_pointer = std::make_shared<int>(42);
    if (auto shared_pointer(weak_pointer.lock()); shared_pointer != nullptr) {
        // shared ��ü�� ��� ����
    }
    else {
        // shared_pointer ������ ������ �����ϳ� nullptr�̴�
    }
    // shared_pointer ������ ���� �Ұ�


    /*++++++++++++++++++++++++++ exit code ��ȯ�ϴ� window�� kernel API function +++++++++++++++++++++++++++*/
    // �־��� �ڵ��� ������ ��쿡�� �ش� ���μ��� �ڵ��� exit �ڵ带 ��ȯ
    if (DWORD exit_code; GetExitCodeProcess(process_handle, &exit_code)) {

        std::cout << "Exit code of process was: " << exit_code << '\n';
    }
        // if ���ǹ� �ܺο����� exit_code ������ ������ �ʴ´�
    ��
    return 0;
}
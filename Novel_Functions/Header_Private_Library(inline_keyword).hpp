# include <iostream>

// ������ �Լ� inline�� �����ߴ� �ݸ� ���� ���� inline�� �����ϴ�

/*+++++++++++++++++++ Before C++17 ++++++++++++++++++++++++++++++*/
// �������� ��⿡ ����� include�Ǿ ��𼭵� ���� �ν��Ͻ��� ���� ����
// �׷��� �ش� ��ü�� ���α׷��� ������ �ƴ� ù �Լ� ȣ�� �ÿ��� �����Ǳ⿡ �Լ� ȣ�� ������ �ʿ��� �۾��� �ִ� ��쿡�� ����� �� ����
// �ذ�å���δ� Ŭ���� ���ø��� ����� ����� �ִ�
class Foo
{
public:
    static std::string& standard_string()  // static ��ü�� reference�� ��ȯ�ϴ� static�Լ�
    {
        static std::string s{ "some standard string" };
        return s;
    }
};


/* ++++++++++++++++++++++++++++++++ After C++17 +++++++++++++++++++++++++++++++++++*/

class Process_Monitor
{
public:
    static const inline std::string standard_string   // inline Ű���带 ���� ��Ŀ�� ������ signature�� �� ���� ���� ���� symbol�� ã�� ���
        { "some static globally available string" };  // ù ��° �ɺ��� �����ϰ� �ٸ� �ɺ��� ���� ���Ǹ� ������ �ִٰ� �ŷ��Ѵ�
};

inline Process_Monitor global_process_monitor;

// ���Ͱ��� ��������� inline Ű���� ���� ������ ���� ��� �� ��������� include�� ��� ��⿡�� Process_Monitor::standard_string�� global_process_monitor �ɺ��� ã�� ���̴�
// �̷� ���� ODR; One Definition Rule �浹�� �߻��Ѵ�
// �� ���� ���� inline �ɺ��� �����ϰ� �Ǹ� ù ��° �����ϴ� �ɺ��� ����ϰ� ������ �ɺ��� ������
# include <iostream>


template <typename T1, typename T2, typename T3>
class My_Wrapper {
    T1 t1;
    T2 t2;
    T3 t3;

public:
    explicit My_Wrapper(T1 t1_, T2 t2_, T3 t3_)   // ������
        : t1{t1_}, t2{t2_}, t3{t3_}
    {}

};

// C++17 ������ ����ϴ� ���� �Լ�
template <typename T1, typename T2, typename T3>
My_Wrapper<T1, T2, T3> Make_Wrapper(T1 t1_, T2 t2_, T3 t3_) {
    return { t1_, t2_, t3_ };
}

template <typename T>
struct Sum {
    T value;      // value��� ���

    template<typename ... Ts>   // �Լ� ���ø�
    Sum(Ts&& ... values) : value{(values + ...)}{}  // Sum�̶�� �Լ� ȣ���� �Ͼ�� value��� ����� Sum�� ���ڵ��� ������ �ʱ�ȭ
};

template<typename ... Ts>
Sum(Ts&& ... ts) -> Sum < std::common_type_t<Ts...>>;  // �ν��ͽ�ȭ ��ų �� Sum�� ���ڷ� �־��ִ� ������ �ڷ����� common_type_t Ư������ Ȱ���Ͽ� �߷��϶�


int main() {

    // �ѹ��� Ư��ȭ �� �ν��Ͻ� ���� ����
    std::pair my_pair(123, "abc"); // std::pair<int, const char*>
    std::tuple my_tuple(123, 12.3, "abc"); // std::tuple<int, double, const char*>

    // before C++17
    My_Wrapper<int, double, const char*> wrapper{ 123, 12.3, "abc" };
    
    auto wrapper(Make_Wrapper(123, 12.3, "abd"));  // �����Լ��� ������ �޾Ҿ���


    // after C++17
    My_Wrapper wrapper{ 123, 12.3, "abc" };

    Sum s           { 1u, 2.0, 3, 4.0f };   // unsigned, double, int float���� �ν��Ͻ�ȭ  ->  common_type_t�� double���� �⺻ �ڷ������� ��ȯ
    Sum str_sum     { std::string{"abc"}, "def" };   // string Ŭ������ char[4]�� �ν��Ͻ�ȭ -> common_type_t�� �߷� ���̵忡 ���� std::string �ڷ������� ��ȯ

    std::cout << s.value << '\n'      // 10
        << str_sum.value << '\n';     // abcdef

    return 0;
}
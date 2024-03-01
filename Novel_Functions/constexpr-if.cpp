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

    // std::enable_if_t<condition, type>�� ���ǽ��� ���� ��� Ÿ���� ���Ѵ�
    // �� ������ add �Լ����� ���� ������ �ݴ�� ��������ν� �� ���� ���� �� �ϳ��� true�� �� �� �ִ�. �׷����� �̷��� ������ ������ �ƴϴ�
    // SFINAE; Substitution Failure Is Not An Error ��Ģ�� ���� ���� �� ���� ���� �� �ϳ����� �߸��� ���ø� ǥ�������� ���� ��ȯ���� �߸��Ǵ��� ������ �߻��Ǵ� ���� �ƴ� �ܼ��� �ٸ� �Լ� ������ �õ��� �� ���̴�
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
    Addable(T v)    // ������ �����ε�
        : val{v}    // T Ŭ������ val ������ v�� �߰�ȣ �ʱ�ȭ
    {

    }

    template<typename U>
    T add(U x) const     // T Ŭ������ ��ȯ�ϴ� add �Լ� ���ø� -> constŰ����� ���� �� �Լ��� ��ü�� ��������� ������ �� ����
    {
        // std::is_same<A, B>�� ��� A�� B�� ���� type���� ���θ� Boolean������ ��ȯ�Ѵ�
        // ���⼭ ���� constexpr-if�� ���ǽ��� std::is_same<T, std::vector<U>>::value �̴�
        // T�� std::vector<X>�� Ư��ȭ �� true������ ���ϰ� U�� XŸ���� �Ű������� �Ͽ� add�Լ��� ȣ���Ѵ�
        if constexpr (std::is_same_v<T, std::vector<U>>) { // ���� T�� std::vector<U>�� ������ ��쿡�� ������ �� ��ҿ� �ش� ���� ���ؾ� �Ѵ�
            auto copy(val);    // ������ �纻 ���ϱ�
            for (auto &n : copy) {   // ������ ���� ��ҿ� �ش� �� ���ϱ�
                n += x;
            }
            return copy;
        }
        else {   // ���Ͱ� �ƴ� ���� �׳� ���Ѵ�
            return val + x;
        }
    }
};


int main() {

    Addable<int>{1}.add(2);                 // 3
    Addable<float>{1.0}.add(2);             // 3.0
    Addable<std::string>{"aa"}.add("bb");   // aabb

    std::vector<int> v{ 1, 2, 3 };
    Addable<std::vector<int>>{v}.add(10);   // v�� �� ��ҿ� 10�� ���ϸ� std::vector<int>{11, 12, 13} �� �ȴ�

    std::vector<std::string> sv{ "a", "b", "c"};
    Addable<std::vector<std::string>>{sv}.add(std::string{ "z" });  // sv�� �� ��ҿ� std::string{"z"}�� ���ϸ� std::Vector<std::string>>{"az", "bz", "cz"}�� �ȴ�


    // constexpr-if�� �Ϲ������� if-else�� �ϴ� ���� ���������� �˻��ϴ� ������ ������ Ÿ�ӿ� �򰡵Ǿ�� �Ѵ�
    // �����Ϸ��� ������ ��Ÿ�� �ڵ�� constexpr-if ���� �б� ����� �������� �ʴ´�
    // ��� constexpr-if�б� ����� ������ �¾ƾ� ������ �׷��� ���� �б� ����� �ǹ̻� ��ȿ�� �ʿ�� ����
    // �ϳ��� constexpr-if-else ��Ͽ� �������� ������ ���� �� �ִ�
    if constexpr (a) {
        // �۾� ����
    }
    else if constexpr (b) {
        // �ٸ� �۾� ����
    }
    else {
        // �ƿ� �ٸ� �۾� ����
    }

    return 0;
}
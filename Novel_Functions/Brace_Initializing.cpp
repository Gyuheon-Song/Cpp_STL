# include <iostream>
# include <vector>

int main() {

    /* ++++++++++++++++++++++ auto �ڷ����� �߷� ���� �߰�ȣ �ʱ�ȭ +++++++++++++++++++++++++*/

    // int�� �ʱ�ȭ�ϴ� ������ ������ ���
    int x1 = 1; 
    int x2(1);
    int x3{ 1 };

    // vector �ʱ�ȭ
    std::vector<int> v1 = { 1, 2, 3 }; // 1, 2, 3 ������ int���� ������ ����
    std::vector<int> v2(10, 20);   // 10���� int�� 20�� ������ ����
    std::vector<int> v3{ 1, 2, 3 }; // 1, 2, 3 ������ int���� ������ ����

    // auto �ڷ����� �߷����� �߰�ȣ �ʱ�ȭ
    auto v{ 1 };  // v�� int 1
    auto x{ 1, 2 };  // error : �߰�ȣ �ʱ�ȭ �ÿ��� �߰�ȣ �ȿ� ���� ��Ҹ� ����
    auto x = { 1 }; // x�� std::initializer_list<int> {1}
    auto y = { 1, 2 }; // y�� std::initializer_list<int> {1, 2}
    auto z = { 1, 2, 3.0 };  // �ڷ��� �߷� �Ұ�

    // �迭�̳� Ŭ����, ����ü ���� ����ü ��� �߰�ȣ �ʱ�ȭ�� �ϰ� �Ǹ�
    // std::initializer_list<type> �����ڿ� ��ġ�ϰ� �Ǹ鼭 �ʱ�ȭ�� �����ϴ�

    // �ݸ�, ������ü�� ��� ������� �ʱ�ȭ�� �Ұ��� �Ӵ���, auto�� ����ϴ� ��쿡�� ���� ��Ҹ� �߰�ȣ �ʱ�ȭ�� �����ϴ�


    // ()�����ڿ� {}�������� ��
    // ()�� ��� ���� ������ �����ڸ� ã�� �Ͻ��� ����ȯ �߻�
    int x(1.2);   // int x�� 1�� ����ȴ�
    // {}�� ��� ������ �����ڸ� �����ϱ⸸ �� �� �Ͻ��� ����ȯ�� �Ͼ�� �ʴ´�
    int x{ 1.2 }; // ������ �Ұ�


    auto var_name{ one_element }; // one_element�� ���� �ڷ����� �ǵ��� auto �߷�
    auto var_name{ element1, element2, ... };  // ������ �Ұ�
    auto var_name = { element1, element2, element3,... };  // ����� ��� ��Ұ� ���� �ڷ����� �ǵ��� std::initializer_list<�ڷ���> �߷�
    
    return 0;
}
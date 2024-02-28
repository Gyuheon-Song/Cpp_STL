# include <iostream>
# include <tuple>
# include <chrono>
# include <string>
# include <vector>
# include <map>

std::pair<int, int> Divide_remainder(int _dend, int _divi) {  // �������� ���� pair�� ��ȯ�ϴ� �Լ�
    int fraction = _dend / _divi;
    int remainder = _dend % _divi;
    return { fraction, remainder };
}


std::tuple<std::string, std::chrono::system_clock::time_point, unsigned> Stock_info(const std::string& name) {
    std::chrono::system_clock::time_point valid_time = std::chrono::system_clock::now();
    unsigned price = 800; 
    return std::make_tuple(name, valid_time, price);
}

struct employee {  // ���� ���� ����ü
    unsigned id;
    std::string name;
    std::string role;
    unsigned salary;
};

int main() {

    /*+++++++++++ C++17 ������ Unpacking ++++++++++++*/

    std::pair<int, int> Divide_remainder(int dividend, int divisor);   // ��� �������� pair�� ��ȯ�ϴ� �Լ�

    // pair������ �� ���� ����
    const std::pair<int, int> result = Divide_remainder(16, 3);
    std::cout << "16 / 3 is "
        << result.first << "with a remainder of "
        << result.second << '\n';


    /*++++++++++++ C++17 ������ Unpacking ++++++++++++*/
    auto [fraction, remainder] = Divide_remainder(16, 3);
    std::cout << "16 / 3 is "
        << fraction << " with a remainder of "
        << remainder << '\n';


    /*++++++++++++++++++++++ tuple������ Structured Binding +++++++++++++++++++++*/
    // �¶��� �ֽ� ������ ���ϴ� �Լ�
    std::tuple<std::string, std::chrono::system_clock::time_point, unsigned> Stock_info(const std::string & name);

    // �̸�, �ŷ� �ð�, ������ Unpacking
    const auto [name, valid_time, price] = Stock_info("NVIDIA");


        /*++++++++++++++++++++++ ����ü������ Structured Binding +++++++++++++++++++++*/
    std::vector<employee> employees;

    for (const auto &[id, name, role, salary] : employees) {
        std::cout << "Name: " << name
            << "Role: " << role
            << "Salary: " << salary << '\n';
    }


    /*++++++++++++++++++++ Structured Binding�� ���� ++++++++++++++++++*/

    //  auto [var1, var2, var3, ...] = <pair, tuple, map, struct �Ǵ� array ǥ����>
    // unpacking�ϴ� �������� �Ҵ�� ǥ����(�ڷᱸ��)�� ���ԵǴ� ������ ������ ��ġ�ؾ� �Ѵ� -> �ٸ� ��� ������ ����
    // unpacking������ �ڷ���
    //  1. std::pair
    //  2. std::tuple
    //  3. struct
    //      - ��� ��������� �������̸� ������ �⺻ Ŭ�������� ���ǵǾ�� �Ѵ�
    //      - ��� ������ ������ ������ ���� unpacking�ȴ�
    //  4. �����迭
    // �ڷ����� auto, const auto, const auto&, auto&&, ... �� �� �� �ִ�

    /*++++++++++++++++ C++17 +++++++++++++++++++++++++++*/
    std::map<std::string, size_t> animal_population{
        {"camels", 36542600},
        {"sheep", 1064500000}
    };
    animal_population.insert({ "humans", 7000000000 });
    animal_population.insert({ "chickens", 1127364500000 });
    
    // std::map �����̳ʸ� ��ȸ�ϸ鼭 std::pair<const key_type, value_type> ��带 ���� ����
    for (const auto& [species, count] : animal_population) {
        std::cout << "There are " << count << ' ' << species
            << " on this planet.\n";
    }

    /*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
    // C++17 ���������� std::tie�� ���� ����ü ���� ���ε� ���� ����
    // std::ignore�� ���� �ʿ���� ���� ���̺��� ó���� �� �� �ִ� ������ �ִ�
    int remainder;
    std::tie(std::ignore, remainder) = Divide_remainder(16, 5);
    std::cout << "16 % 5 is " << remainder << '\n';



    /*++++++++++++++++++++++ RVO; Return Value Optimization +++++++++++++++++++*/
    // �ֱ� �����Ϸ������� �Լ��� ������ ����ü�� ��ȯ�ϴ��� �߰� ���� ����(��ȯ�Ǵ� �Լ� ������ ��ü �ʱ�ȭ �� ȣ���ϴ� ���� ������ ����)�� �����Ѵ�

    return 0;
}
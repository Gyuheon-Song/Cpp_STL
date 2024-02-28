# include <iostream>

std::pair<int, int> Divide_remainder(int _dend, int _divi) {
    return std::make_pair(_dend / _divi, _dend % _divi);
}


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
        << fraction << "with a remainder of "
        << remainder << '\n';












    return 0;
}
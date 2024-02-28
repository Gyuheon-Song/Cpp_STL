# include <iostream>

std::pair<int, int> Divide_remainder(int _dend, int _divi) {
    return std::make_pair(_dend / _divi, _dend % _divi);
}


int main() {

    /*+++++++++++ C++17 이전의 Unpacking ++++++++++++*/

    std::pair<int, int> Divide_remainder(int dividend, int divisor);   // 몫과 나머지를 pair로 반환하는 함수

    // pair변수의 각 값에 접근
    const std::pair<int, int> result = Divide_remainder(16, 3);
    std::cout << "16 / 3 is "
        << result.first << "with a remainder of "
        << result.second << '\n';


    /*++++++++++++ C++17 이후의 Unpacking ++++++++++++*/

    auto [fraction, remainder] = Divide_remainder(16, 3);
    std::cout << "16 / 3 is "
        << fraction << "with a remainder of "
        << remainder << '\n';












    return 0;
}
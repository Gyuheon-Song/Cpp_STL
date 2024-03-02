# include <iostream>
# include <vector>
# include <set>


template<typename ... Ts>    // Signature�� ���� �����Ѵ�(�Լ� ���ø�)
auto Sum(Ts ... ts);         // Sum�� ���ڴ� Ts Ÿ���� ���ڵ��� �Ű����� ts�� �ȴ�

template<typename ... Ts>  // Sum �Լ� ���� 
auto Sum(Ts ... ts)
{   // ���� ���� ���� ����
    return (ts + ... + 0);   // ts�� +�� ...�� ���� ��� ���ڸ� ���ļ� ������ �����Ѵ� -> Folding
    // ���� Sum()�� ȣ��Ǿ� ���� parameter ������ ���� �� �ִ� ���� ���Ե��� ���� ��� �����߻� ���� �� �� �հ踦 0���� Ư���� �� �ֵ��� + 0 �� ���־� �ĺ����� 0���� ���ش�
}

// Folding�� �����ϴ� ������
// +, -, *, /, %, ^, |, =, &, <, >, <<, >>, +=, -=, *=, /=, %=, ^=, &=, |=, <<=, >>=, ==, !=, <=, >=, &&, ||, ,, .*, ->*

template<typename ... Ts>
auto Product(Ts ... ts)
{
    return (ts * ... * 1);   // ���⼭ �����ϴ� ���������� �ĺ����� 1�� �ߴ� -> ���ڰ� ������ �ʴ� ��� 1�� ��ȯ
}

// && �� || ���� ��� ����� ��ü �ĺ��ڸ� ������
// &&�� ��� �ĺ��� true
// ||�� ��� �ĺ��� false


template<typename R, typename ... Ts>
auto Matches(const R& range, Ts ... ts)  // Helper Function
{
    // std::count�� ������ ���ڸ� �޴´� -> �ݺ� ������ ������ ���� iterator, �ݺ� ������ ������ �� iterator, ������ �� ��
    return (std::count(std::begin(range), std::end(range), ts) + ...);
    // Fold Expression�� ���� count()�Լ��� ts�� ������ �ִ� ��� ����� ������ ��ȯ�Ѵ�
    // Fold Expression�� ���� �� ���������� count()�Լ��� ���� range�� ���۰� �� iterator�� �����ϸ� ����° ���ڸ� �ٸ� parameter�� �����Ѵ�

    // std::list, std::array, std::set, std::initializer_list���� �ν��Ͻ����� �����ϰ� ����
}


// set�� ����
// set�� �����Լ��� ������ signature : std::pair<iterator, bool> insert(const value_type& value)
// insert�Լ��� iterator�� bool�� ��ȯ�Ѵ� -> ���� ���� �� true�� �Բ� set�� �߰��� ���ο� ��Ҹ� iterator�� ����Ų��
                                        //  ���� ���� �� false�� �Բ� �����Ϸ��ϴ� ���� �浹�Ǵ� ���� ��Ҹ� iterator�� ����Ų��
template <typename T, typename ... Ts>
bool Insert_All(T& set, Ts ... ts)   // helper function
{
    // �������� ������ �� second�� ���� = bool��
    // fold expression���� && ������ ����Ͽ� ��� ������ �����ߴ��� ���� �Ǵ�
    // ���ڵ� �� �߰��� � ��Ұ� ���� ���� �� ��� �ٸ� ����� ���Ե� �����ϰ� �ȴ�
    return (set.insert(ts).second && ...);
}


// � ������ ���� �������� �� ���ϴ��� �˻�
template <typename T, typename ... Ts>
bool Within(T min, T max, Ts ... ts)
{
    return ((min <= ts && ts <= max) && ...);  // ��� �������� min�� max ���̿� �����ϴ��� && �������� ������ ����
}


/*+++++++++++++++++++++ vector�� �������� ��� �ֱ� +++++++++++++++++++++++++++*/
template <typename T, typename ... Ts>
void InsertAll(std::vector<T>& vec, Ts ... ts)
{
    (vec.push_back(ts), ...);   //  , �� ��������ν� ������� ǥ���� ���⸦ ���� ���� �ƴ� ���� vec.push_back(...)���� parameter������ ��ģ��
}                               // , �� �Ͻ����� �ĺ� �� void()�� ������ �ֱ⿡ ���ڰ� ���� ��� �� �۵��Ѵ�


int main() {

    // ... + ts
    // 1 + (2 + (3 + (4 + 5)))  : ���� �������� -> �������� �����
    
    // ts + ...  
    // (((1 + 2) + 3) + 4) + 5  : ������ �������� -> ���������� �����

    //�ʱ갪�� ���� ���� ���� Binary Fold��� �Ѵ�
    // ts + ... + 0  ������ ���� Binary Fold
    // 0 + ... + ts  ���� ���� Binary Fold

    int the_sum{ Sum(1, 2, 3, 4, 5) };      // the_sum �� : 15

    std::string a{ "Hello " };
    std::string b{ "World" };
    std::cout << Sum(a, b) << '\n';   // Hello World


    std::vector<int> v{ 1, 2, 3, 4, 5 };

    Matches(v, 2, 5);       // v ���� �ȿ� 2�� 1�� 5�� 1�� �̹Ƿ� 1+1 = 2 ��ȯ
    Matches(v, 100, 200);    // 0 ��ȯ
    Matches("abcdefg", 'x', 'y', 'z');  // 0 ��ȯ
    Matches("abcdefg", 'a', 'd', 'f');  // 3 ��ȯ


    /*++++++++++++++ set�� �������� ���� ���� ���� Ȯ�� ++++++++++++++++++++++++*/
    std::set<int> my_set{ 1, 2, 3 };
    Insert_All(my_set, 4, 5, 6);        // true
    Insert_All(my_set, 7, 8, 2);        // 2 ���� �浹�� false

    std::set<int> my_set{ 1, 2, 3 };
    Insert_All(my_set, 4, 2, 5);        // 2 �� �����ϸ鼭 false�� ��ȯ�Ѵ� -> 5�� �����ϴ� �۾��� ������� �ʴ´�
    // my_set�� {1, 2, 3, 4}�� �����̴�
    

    /*++++++++++++++++++++ ��� �������� � ������ ����ִ��� �˻� +++++++++++++++++++++++++++++*/
    Within(10, 20, 1, 15, 30);   // 30�� 10�� 20������ ���� �ƴϹǷ� false ��ȯ
    Within(10, 20, 11, 12, 13);  // ��� ���� 10�� 20 ������ ���̹Ƿ� true ��ȯ
    Within(5.0, 5.5, 5.1, 5.2, 5.3);   // true ��ȯ

    // std::string Ŭ������ ����ϸ� ������ ���� �ȿ� ���ϴ��� ���� �˻� ����
    std::string aaa{ "aaa" };
    std::string bcd{ "bcd" };
    std::string def{ "def" };
    std::string zzz{ "zzz" };
    Within(aaa, zzz, bcd, def);   // true
    Within(aaa, def, bcd, zzz);   // false


    /* +++++++++++++++++++++ vector�� �������� ��Ҹ� �ִ� �����Լ� +++++++++++++++++++++++++++++++*/
    std::vector<int> vv{ 1, 2, 3 };
    InsertAll(vv, 4, 5, 6);    // vv{1, 2, 3, 4, 5, 6}
    InsertAll(vv);             // vv{1, 2, 3, 4, 5, 6}  ���ڰ� ��� �۵��� �� �ֵ��� ���� �Լ��� ������ ���Ҵ�

    return 0;
}
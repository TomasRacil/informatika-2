#include <iostream>
#include <vector>
#include <algorithm>

class Student
{
private:
public:
    std::string name;
    int prumer;
    Student(const Student &other)
    {
        this->name = other.name;
        this->prumer = other.prumer;
    }
    Student(std::string name, int prumer)
    {
        this->name = name;
        this->prumer = prumer;
    }
    bool operator<(Student other)
    {
        return prumer < other.prumer;
    }

    bool operator==(Student other)
    {
        return (name == other.name && prumer == other.prumer);
    }

    friend std::ostream &operator<<(std::ostream &os, const Student &v);
};

std::ostream &operator<<(std::ostream &os, const Student &v)
{
    // Definujeme formát výpisu
    os << "Vektor(" << v.name << ", " << v.prumer << ")";
    return os;
}

template <typename T>
void print_vector(std::vector<T> v)
{
    for (T hodnota : v)
    {
        std::cout << hodnota << ", ";
    }
    std::cout << std::endl;
}

int main()
{
    std::vector<int> v = {10, 2, 8, 15, 6};
    print_vector(v);
    std::sort(v.begin(), v.end());
    print_vector(v);

    std::vector<Student> vs = {Student("Pepa", 2), Student("Jonas", 1), Student("Jakub", 3)};
    print_vector(vs);
    std::sort(vs.begin(), vs.end());
    print_vector(vs);
    auto it = std::find(vs.begin(), vs.end(), Student("Jonas", 1));
    std::cout << *it << std::endl;
    Student t("AD", 2);
    Student s = t;

    // std::vector<int> v = {1, 2, 3};
    std::for_each(v.begin(), v.end(), [](int x)
                  { std::cout << x << " "; });

    int limit = 3;

    auto vit = std::find_if(v.begin(), v.end(), [limit](int x)
                            { return x > limit; });

    if (vit != v.end())
    {
        std::cout << "Prvni prvek > 3 je: " << *vit << std::endl;
    }

    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2(v1.size()); // Cílový vektor musí mít dostatek místa

    // Zdvojnásobí každý prvek z v1 a uloží ho do v2
    std::transform(v1.begin(), v1.end(), v2.begin(), [](int x)
                   { return x * 2; });
    print_vector(v2);

    // Třídění sestupně
    std::sort(vs.begin(), vs.end(), [](Student a, Student b)
              {
                  return a.name > b.name; // Vrať true, pokud 'a' má být PŘED 'b'
              });

    print_vector(vs);

    //     1. Filtrace
    // Máte vektor čísel {1, 5, 8, 9, 12, 4, 7}. Použijte std::count_if s lambda funkcí, abyste zjistili, kolik čísel je větších než 6.
    std::vector<int> c = {1, 5, 8, 9, 12, 4, 7};
    limit = 6;
    int count = std::count_if(c.begin(), c.end(), [limit](int x) -> bool
                              { return x > limit; });

    std::cout << count << std::endl;

    // 2. Vlastní řazení
    // Máte vektor stringů {"Jablko", "Banán", "Ananas", "Hruška"}. Seřaďte je pomocí std::sort podle délky slova (od nejkratšího).
    std::vector<std::string> sort_s = {"Jablko", "Banan", "Ananas", "Hruska"};
    std::sort(sort_s.begin(), sort_s.end(), [](std::string a, std::string b)
              { return a.length() < b.length(); });

    print_vector(sort_s);

    // 3. Transformace
    // Máte vektor čísel. Pomocí std::transform vytvořte nový vektor, který bude obsahovat druhé mocniny čísel z prvního vektoru.
    std::vector<int> v3(v.size());
    std::transform(v.begin(), v.end(), v3.begin(), [](int x)
                   { return x * x; });
    print_vector(v3);

    return 0;
}
#include <iostream>

class KomplexniCislo
{
private:
    double realna;
    double imaginarni;

public:
    KomplexniCislo(double realna, double imaginarni);
    KomplexniCislo operator+(KomplexniCislo other);
    friend std::ostream& operator<<(std::ostream& os, const KomplexniCislo& k);
    ~KomplexniCislo();
};

KomplexniCislo::KomplexniCislo(double realna, double imaginarni)
{
    this->realna = realna;
    this->imaginarni = imaginarni;
}

KomplexniCislo KomplexniCislo::operator+(KomplexniCislo other)
{
    return KomplexniCislo(
        this->realna + other.realna, 
        this->imaginarni + other.imaginarni);
}

KomplexniCislo::~KomplexniCislo()
{
}

int main()
{   
    KomplexniCislo a = KomplexniCislo(5,5);
    KomplexniCislo b = KomplexniCislo(4,3);

    KomplexniCislo c = a+b;

    std::cout<<a<<" + "<<b<<" = "<<c<<std::endl;

    return 0;
}

std::ostream &operator<<(std::ostream &os, const KomplexniCislo &k)
{
    os<<"("<<k.realna<<" + "<<k.imaginarni<<"i)";
    return os;
}

#include <iostream>
#include <ios> // Required for std::ios_base::failbit and std::ios_base::failure

using namespace std;

int main()
{
    // int znamka;

    // cout << "Zadej znamku: ";

    cin.exceptions(ios_base::failbit | ios_base::badbit);

    // try
    // {
    //     cin >> znamka;
    //     if (znamka < 0 || znamka > 100)
    //     {
    //         throw out_of_range("Neplatna hodnota. Hodnota musi byt v rozsahu 0-100.");
    //     }

    //     if (znamka >= 90)
    //     {
    //         cout << "A";
    //     }
    //     else if (znamka >= 80)
    //     {
    //         cout << "B";
    //     }
    //     else if (znamka >= 70)
    //     {
    //         cout << "C";
    //     }
    //     else if (znamka >= 60)
    //     {
    //         cout << "D";
    //     }
    //     else if (znamka > 0)
    //     {
    //         cout << "F";
    //     }
    // }
    // catch (runtime_error e)
    // {
    //     cout << "Nastal rutime error." << endl;
    //     cerr << e.what();
    // }
    // catch (exception e)
    // {
    //     cout << "Nastala jina chyba" << endl;
    //     cerr << e.what();
    // }

    // int den;

    // cin >> den;

    // switch (den)
    // {
    // case 1:
    //     std::cout << "Pondeli" << std::endl;
    //     break;
    // case 2:
    //     std::cout << "Utery." << std::endl;
    //     break;
    // case 3:
    //     std::cout << "Streda." << std::endl;
    //     break;
    // default:
    //     std::cout << "Neplatna hodnota" << std::endl;
    //     break;
    // }

    int a, b;
    try
    {
        cout << "Vydel dve cisla." << endl
             << "Zadej prvni cislo: ";
        cin >> a;
        cout << "Zadej druhe cislo: ";
        cin >> b;
        if (b == 0)
            throw runtime_error("deleni nulou");
        cout << a / b << endl;
    }
    catch (exception e)
    {
        cerr << e.what() << endl;
    }

    return 0;
}
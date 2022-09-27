#include <algorithm>
#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <string.h>
#include <fstream>
using namespace std;
//Задание 1.
//Создайте приложение для работы автосалона.Необходимо
//хранить информацию о продаваемых автомобилях(название, 
//    год выпуска, объем двигателя, цену).Реализуйте
//интерфейс для добавления данных, удаления данных,
//отображения данных, сортировке данных по различным
//параметрам, поиску данных по различным параметрам.
//При реализации используйте контейнеры, функторы
//и алгоритмы.

//Задание 3.
//Измените функторы из первого задания в шаблонные
//классы - функторов.Проверьте работу полученного решения на разных 
//контейнерах с разным содержимым.

template <typename T1, typename T2>
class Auto_total
{
    T1 count = 0;
    T2 sum = 0;
public:
    void operator()(T2 sumP)
    {
        sum += sumP;

        if (sumP > 0)
            count++;
        else if (sumP < 0)
            count--;
    }
    void show_count() const
    {
        cout << "There are " << count << " cars in the shop.\n";
    }
    void show_sum() const
    {
        cout << "Total price of all cars is  USD " << sum << ".\n";
    }
};
Auto_total<int, double> a_total;

class Auto
{
    string name;
    int prod_year;
    int engine_volume;
    double price;
public:
    Auto(string nameP, int prod_yearP, int engine_volumeP, double priceP);
    Auto();
    string get_name() const;
    int get_prod_year() const;
    int get_engine_volume() const;
    double get_price() const;
    void set_name(string nameP);
    void set_prod_year(int prod_yearP);
    void set_engine_volume(int engine_volumeP);
    void set_price(double priceP);
    void show_car();
    bool operator==(const Auto& object);
    friend ostream& operator<<(ostream& out, const Auto& object);
};
Auto::Auto(string nameP, int prod_yearP, int engine_volumeP, double priceP) :
    name{ nameP }, prod_year{ prod_yearP }, engine_volume{ engine_volumeP },
    price{ priceP }{ }
Auto::Auto() : Auto("", 0, 0, 0) {}
string Auto::get_name() const { return name; }
int Auto::get_prod_year() const { return prod_year; }
int Auto::get_engine_volume() const { return engine_volume; }
double Auto::get_price() const { return price; }
void Auto::set_name(string nameP) { name = nameP; }
void Auto::set_prod_year(int prod_yearP) { prod_year = prod_yearP; }
void Auto::set_engine_volume(int engine_volumeP) { engine_volume = engine_volumeP; }
void Auto::set_price(double priceP) { 
    price = priceP; 
}
void Auto::show_car() {

    cout << "Model: " << name << endl;
    cout << "Year of production: " << prod_year << endl;
    cout << "Engine volume: " << engine_volume << endl;
    cout << "Price, USD: " << price << endl;
    cout << endl;
}
ostream& operator<<(ostream& out, const Auto& object) {

    cout << "Model: " << object.name << endl;
    cout << "Year of production: " << object.prod_year << endl;
    cout << "Engine volume: " << object.engine_volume << endl;
    cout << "Price, USD: " << object.price << endl;
    cout << endl;
    return out;
}
bool Auto::operator==(const Auto& object)
{
    bool i = 1;

    if (name != object.name)
        i = 0;

    if (prod_year != object.prod_year)
        i = 0;

    if (engine_volume != object.engine_volume)
        i = 0;

    if (price != object.price)
        i = 0;

    return i;
}

bool SortByName(Auto& left, Auto& right)
{
    return (left.get_name() < right.get_name());
}
bool SortByProdYear(Auto& left, Auto& right)
{
    return (left.get_prod_year() < right.get_prod_year());
}
bool SortByEngineVolume(Auto& left, Auto& right)
{
    return (left.get_engine_volume() < right.get_engine_volume());
}
bool SortByPrice(Auto& left, Auto& right)
{
    return (left.get_price() < right.get_price());
}

Auto Add_Auto()
{
    string nameP;
    Auto temp;
    int t1;
    double t2;


    cout << "\nname: ";
    cin >> nameP;
    temp.set_name(nameP);

    cout << "production yaer: ";
    cin >> t1;
    temp.set_prod_year(t1);

    cout << "engine volume: ";
    cin >> t1;
    temp.set_engine_volume(t1);

    cout << "price: ";
    cin >> t2;
    temp.set_price(t2);
    a_total(t2);

    return temp;
}
void Edit_Auto(list<Auto>& a, int i)
{
    if (i<1 || i > a.size())
        throw "\nWrong index!!!\n";

    string nameP;
    int t1;
    double t2;

    auto it = a.begin();
    advance(it, i - 1);

    cout << "\nname: ";
    cin >> nameP;
    (*it).set_name(nameP);

    cout << "production yaer: ";
    cin >> t1;
    (*it).set_prod_year(t1);

    cout << "engine volume: ";
    cin >> t1;
    (*it).set_engine_volume(t1);

    a_total(-(*it).get_price());

    cout << "price: ";
    cin >> t2;
    (*it).set_price(t2);

    a_total((*it).get_price());

}
void Delete_Auto(list<Auto>& a, int i)
{
    if (i<1 || i > a.size())
        throw "\nWrong index!!!\n";

    auto it = a.begin();
    advance(it, i - 1);

    a_total(-(*it).get_price());
    a.erase(it);
}


void SaveToFile(list<Auto>& l_auto)
{
    remove("Autos.txt");

    int size; char* temp = nullptr;
    double size_d;

    fstream f("Autos.txt", ios::out | ios::binary | ios::app);

    if (!f)
    {
        throw "\nFile is not opened for writing!\n";
    }

    for (auto var : l_auto)
    {
        if (temp != nullptr)
            delete[] temp;

        size = var.get_name().size();
        f.write((char*)&size, sizeof(int));
        temp = new char[size + 1];
        strcpy_s(temp, size + 1, var.get_name().c_str());
        f.write((char*)temp, size * sizeof(char));

        size = var.get_prod_year();
        f.write((char*)&size, sizeof(int));

        size = var.get_engine_volume();
        f.write((char*)&size, sizeof(int));

        size_d = var.get_price();
        f.write((char*)&size_d, sizeof(double));
    }

    f.close();
    delete[] temp;
}
list<Auto> LoadFromFile() {
    fstream f("Autos.txt", ios::in | ios::binary);
    if (!f) {
        throw "\nFile is not opened for reading!\n\n";
    }
    char* temp = nullptr;
    int size; double size_d;
    int i = 0;
    list<Auto> auto_temp;

    while (f.read((char*)&size, sizeof(int)))
    {
        Auto a_temp;

        if (temp != nullptr)
            delete[] temp;

        temp = new char[size + 1];
        f.read((char*)temp, size * sizeof(char));
        temp[size] = '\0';
        a_temp.set_name(temp);

        f.read((char*)&size, sizeof(int));
        a_temp.set_prod_year(size);

        f.read((char*)&size, sizeof(int));
        a_temp.set_engine_volume(size);

        f.read((char*)&size_d, sizeof(double));
        a_temp.set_price(size_d);

        a_total(size_d);
        auto_temp.push_back(a_temp);
    }

    delete[] temp;

    return auto_temp;
}

void show_all(const list<Auto> v)
{
    int i = 1;
    for (auto var : v)
    {
        cout << "Car " << i++ << " information:\n";
        var.show_car();
    }
}

int Menu()
{
    int temp;
    cout << "\nPlease make your choice:\n";
    cout << " 1 - to see all autos\n";
    cout << " 2 - to add new auto\n";
    cout << " 3 - to delete auto\n";
    cout << " 4 - to edit auto\n";
    cout << " 5 - to sort data\n";
    cout << " 6 - to find auto\n";
    cout << " 7 - show total number and car value\n";
    cout << " 0 - to exit programm\n";
    cout << "\nYour choice is - ";
    cin >> temp;

    return temp;
}
int Sort_Menu()
{
    int temp;
    cout << "\nPlease make your choice:\n";
    cout << " 1 - to sort by name\n";
    cout << " 2 - to sort by production year\n";
    cout << " 3 - to sort by engine volume\n";
    cout << " 4 - to sort by price\n";
    cout << " 0 - return to main menu\n";
    cout << "\nYour choice is - ";
    cin >> temp;

    return temp;
}
int Find_Menu()
{
    int temp;
    cout << "\nPlease make your choice:\n";
    cout << " 1 - to find by name\n";
    cout << " 2 - to find by production year\n";
    cout << " 3 - to find by engine volume\n";
    cout << " 4 - to find by price\n";
    cout << " 0 - to return to main menu\n";
    cout << "\nYour choice is - ";
    cin >> temp;

    return temp;
}

int main()
{
    {
        //list<Auto> autos = LoadFromFile();

        //try {
        //    int t;

        //    do {
        //        switch (Menu()) {
        //        case 1:
        //            show_all(autos);
        //            break;
        //        case 2:
        //        {
        //            cout << "\nAdditg new car. Please enter";
        //            autos.push_back(Add_Auto());
        //            cout << "new car added!\n";
        //            break;
        //        }
        //        case 3:
        //        {
        //            int temp;
        //            cout << "Please enter car number you want to delete: ";
        //            cin >> temp;
        //            Delete_Auto(autos, temp);
        //            cout << "Car " << temp << " deleted.\n";
        //            break;
        //        }
        //        case 4:
        //        {
        //            int temp;
        //            cout << "\nPlease enter number of car to edit: ";
        //            cin >> temp;

        //            Edit_Auto(autos, temp);
        //            cout << "car edited!\n";
        //            break;
        //        }
        //        case 5:
        //        {
        //            int t2 = 1;

        //            do {
        //                switch (Sort_Menu())
        //                {
        //                case 1:
        //                {
        //                    autos.sort(SortByName);
        //                    show_all(autos);
        //                    break;
        //                }
        //                case 2:
        //                {
        //                    autos.sort(SortByProdYear);
        //                    show_all(autos);
        //                    break;
        //                }
        //                case 3:
        //                {
        //                    autos.sort(SortByEngineVolume);
        //                    show_all(autos);
        //                    break;
        //                }
        //                case 4:
        //                {
        //                    autos.sort(SortByPrice);
        //                    show_all(autos);
        //                    break;
        //                }
        //                case 0:
        //                    t2 = 0;
        //                    break;
        //                default:
        //                    cout << "Wrong choice!\n";
        //                }

        //            } while (t2);

        //            break;
        //        }
        //        case 6:
        //        {
        //            int t3 = 1;

        //            do {
        //                switch (Find_Menu())
        //                {
        //                case 1:
        //                {
        //                    string temp_s;
        //                    cout << "Enter car name: ";
        //                    cin >> temp_s;

        //                    auto it = find_if(autos.begin(), autos.end(),
        //                        [&](Auto& a) { return a.get_name() == temp_s; });

        //                    if (it != autos.cend())
        //                    {
        //                        cout << "There is car with this name\n" << endl;
        //                        cout << *it;
        //                    }
        //                    else
        //                        cout << "There is no car with this name\n" << endl;

        //                    break;
        //                }
        //                case 2:
        //                {
        //                    int temp_year;
        //                    cout << "Enter car production year: ";
        //                    cin >> temp_year;

        //                    auto it = find_if(autos.begin(), autos.end(),
        //                        [&](Auto& a) { return a.get_prod_year() == temp_year; });

        //                    if (it != autos.end())
        //                    {
        //                        cout << "There is car with this production year\n" << endl;
        //                        cout << *it;
        //                    }
        //                    else
        //                        cout << "There is no car with this production year\n" << endl;

        //                    break;
        //                }
        //                case 3:
        //                {
        //                    int temp_eng_vol;
        //                    cout << "Enter car engine volume: ";
        //                    cin >> temp_eng_vol;

        //                    auto it = find_if(autos.begin(), autos.end(),
        //                        [&](Auto& a)
        //                        { return a.get_engine_volume() == temp_eng_vol; });

        //                    if (it != autos.end())
        //                    {
        //                        cout << "There is car with this engine volume\n" << endl;
        //                        cout << *it;
        //                    }
        //                    else
        //                        cout << "There is no car with this engine volume\n" << endl;

        //                    break;
        //                }
        //                case 4:
        //                {
        //                    double temp_price;
        //                    cout << "Enter car price: ";
        //                    cin >> temp_price;

        //                    auto it = find_if(autos.begin(), autos.end(),
        //                        [&](Auto& a) { return a.get_price() == temp_price; });

        //                    if (it != autos.end())
        //                    {
        //                        cout << "There is car with this price\n" << endl;
        //                        cout << *it;
        //                    }
        //                    else
        //                        cout << "There is no car with this price\n" << endl;


        //                    break;
        //                }
        //                case 0:
        //                    t3 = 0;
        //                    break;
        //                default:
        //                    cout << "Wrong choice!\n";
        //                }

        //            } while (t3);

        //            break;
        //        }
        //        case 7:
        //        {
        //            a_total.show_count();
        //            a_total.show_sum();
        //            break;
        //        }
        //        case 0:
        //        {cout << "Good Buy!\n";
        //        SaveToFile(autos);
        //        return 0;
        //        }
        //        default:
        //            cout << "Wrong choice!\n";
        //        }
        //    } while (1);
        //}
        //catch (char* su) {
        //    std::cout << "\n\nException!!!\n\n";
        //}
    }

    cout << "Checking for vector\n";
    vector<float> l1{ 1, 2, 3.2, 123, 1, 2, 3 };
    Auto_total<int, float> a1;

    for (auto var : l1)
        a1(var);

    a1.show_count();
    a1.show_sum();

    cout << "\nChecking for map\n";
    map<string, int> m1{ {"Masha", 12}, {"Petia", 32}, {"Jack", 21} };
    Auto_total<int, int> a2;

    for (auto var : m1)
        a2(var.second);

    a2.show_count();
    a2.show_sum();

    return 0;
}
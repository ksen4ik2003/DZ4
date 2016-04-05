#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct addr_type
{
    char *street;
    char *home;
};



struct zdanie_type
{
    addr_type address;
    char *architect;
    int year;
    char *type;
    int floors;
};


class Building
{
    int n;  //количество объектов, считывается из первой строчки файла
    zdanie_type *zd;

    public:
        Building(int n) {zd = new zdanie_type [n];}
        Building (const Building &ob);
        ~Building();
        void set(zdanie_type zdan, int &num);   //заполнение num-того элемента массива данными, считанными из файла
        zdanie_type get(int &num);
        void show(int &num);
};

Building::Building (const Building &ob)
{
    n = ob.n;
    zd = new zdanie_type [n];
    for(int i = 0; i < n; i++)
        zd[i] = ob.zd[i];
}

Building::~Building()
{
    for(int i = 0; i < n; i++)
        {
            delete [] zd->address.street;
            delete [] zd->address.home;
            delete [] zd->architect;
            delete [] zd->type;
        }
    delete [] zd;
}

void Building::set(zdanie_type zdan, int &num)
{
    if (num < n) //на всякий случай проверяем, не выходим ли за массив
    {
        zd[num].address.street = new char (strlen (zdan.address.street)+1);
        strcpy(zd[num].address.street, zdan.address.street);

        zd[num].address.home = new char (strlen (zdan.address.home)+1);
        strcpy(zd[num].address.home, zdan.address.home);

        zd[num].architect = new char (strlen (zdan.architect)+1);
        strcpy(zd[num].architect, zdan.architect);

        zd[num].year = zdan.year;

        zd[num].type = new char (strlen (zdan.type)+1);
        strcpy(zd[num].type, zdan.type);

        zd[num].floors = zdan.floors;
    }
}

zdanie_type Building::get(int &num)
{
    return zd[num];
}

void Building::show(int &num)
{
    cout << "\n";
    cout << "Street: " << zd[num].address.street<< "\n";
    cout << "Building: " << zd[num].address.home<< "\n";
    cout << "Architect: " << zd[num].architect<< "\n";
    cout << "Year: " << zd[num].year << "\n";
    cout << "Type: " << zd[num].type << "\n";
    cout << "Floors: " << zd[num].floors << "\n";
    cout << "\n";
}

int main()
{
    ifstream file("test.txt");
    if(!file)
        cout << "File not opened";
    else
    {
        int n;
        file >> n;

        Building ob(n);

        for (int i = 0; i < n; i++)
        {
            // объявляем структуру и инициализируем массивы для считывания файла
            zdanie_type zdan;
            zdan.address.street = new char [80];
            zdan.address.home = new char [8];
            zdan.architect = new char [40];
            zdan.type = new char [20];

            //чтение файла, ignore пропускает символ перехода на след строку
            file.ignore();
            file.getline(zdan.address.street, 80);
            file.getline(zdan.address.home, 8);
            file.getline(zdan.architect, 40);
            file >> zdan.year;
            file.ignore();
            file.getline(zdan.type, 20);
            file >> zdan.floors;
            file.ignore();
            ob.set(zdan, i);    //заполнение i-го элемента массива данными, считанными из файла
        }

        char out_type;  //тип выбора объектов

        cout << "Vyberite tip vivoda: \n";
        cout << "1. Spisok zdanij dannogo tipa \n";
        cout << "2. spisok zdanij dannogo architectora opredelennogo tipa \n";
        cout << "3. Spisok zdanij, god postrojki kotorich ranee zadannogo \n";

        cin >> out_type;

        if(out_type == '1')
        {
            char type[20];
            cout << "Vvedite tip zdaniya: \n";
            cin >> type;
            for(int i = 0; i < n; i++)
            {
                zdanie_type zdan;
                zdan = ob.get(i);
                if (!strcmp(zdan.type, type))
                    ob.show(i);
            }
        }
        else if(out_type == '2')
        {
            char name[40];
            cout << "Vvedite architectora: \n";
            cin.ignore();
            cin.get (name, 40);
            char type[20];
            cout << "Vvedite tip zdaniya: \n";
            cin.ignore();
            cin.get(type, 20);
            for(int i = 0; i < n; i++)
            {
                zdanie_type zdan;
                zdan = ob.get(i);
                if (!strcmp(zdan.type, type))
                    if(!strcmp(zdan.architect, name))
                        ob.show(i);
            }
        }
        else if(out_type == '3')
        {
            int year;
            cout << "Vvedite god: \n";
            cin >> year;
            for(int i = 0; i < n; i++)
            {
                zdanie_type zdan;
                zdan = ob.get(i);
                if (zdan.year < year)
                    ob.show(i);
            }
        }
        file.close();
    }

return 0;
}

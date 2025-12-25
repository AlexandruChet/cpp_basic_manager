#include <iostream>
#include <string>
#include <vector>
#include <variant>
#include <ctime>
#include <cstdlib>
#include <fstream>

using namespace std;

struct Product
{
    int id;
    string name;
    string price;
};

class Entity
{
protected:
    string name;
    string email;
    int password;
    int id;

public:
    Entity(string n, string e, int p, int i)
        : name(n), email(e), password(p), id(i) {}

    virtual void save_to_file() = 0;
    virtual void save_info_to_file() = 0;
    virtual void registration() = 0;
    virtual void write_info() = 0;

    virtual ~Entity() {}
};

class User : public Entity
{
public:
    vector<variant<int, string>> reg_information;
    vector<Product> user_products_information;

    User() : Entity("", "", 0, 0) {}

    void registration() override
    {
        cout << "Please write your name: ";
        cin >> name;

        cout << "Please write your email: ";
        cin >> email;

        id = rand() % 100000 + 1;
        cout << "Your id: " << id << endl;

        reg_information.push_back(name);
        reg_information.push_back(email);
        reg_information.push_back(id);
    }

    void save_to_file() override
    {
        ofstream outFile("output.txt");

        if (outFile.is_open())
        {
            for (const auto &element : reg_information)
            {
                if (holds_alternative<int>(element))
                    outFile << get<int>(element) << " ";
                else
                    outFile << get<string>(element) << " ";
            }
            outFile << endl;
        }
        else
        {
            cerr << "Error opening file" << endl;
        }
    }

    void write_info() override
    {
        Product p;
        p.id = rand() % 10000 + 1;

        cout << "Please write your product: ";
        cin >> p.name;

        cout << "Please write your price: ";
        cin >> p.price;

        user_products_information.push_back(p);
    }

    void save_info_to_file() override
    {
        ofstream productFile("product.txt");

        if (productFile.is_open())
        {
            for (const auto &e : user_products_information)
            {
                productFile << e.id << " "
                            << e.name << " "
                            << e.price << endl;
            }
        }
        else
        {
            cerr << "Error opening product file" << endl;
        }
    }
};

int main()
{
    srand(time(nullptr));

    Entity *user = new User();
    user->registration();
    user->save_to_file();

    cout << "If you want to create product press A: ";
    char answer;
    cin >> answer;

    if (answer == 'A')
    {
        user->write_info();
        user->save_info_to_file();
    }

    delete user;
    return 0;
}

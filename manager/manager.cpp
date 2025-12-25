#include <iostream>
#include <string>
#include <vector>
#include <variant>
#include <ctime>
#include <cstdlib>
#include <fstream>

using namespace std;

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
    vector<pair<string, string>> user_products_information;

    User() : Entity("", "", 0, 0) {}

    void registration() override
    {
        cout << "Please write your name: ";
        cin >> name;

        cout << "Please write your email: ";
        cin >> email;

        srand(time(nullptr));
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
        }
        else
        {
            cerr << "Error opening file" << endl;
        }
    }

    void save_info_to_file() override
    {
        ofstream productFile("product.txt");
        if (productFile.is_open())
        {
            for (const auto &e : user_products_information)
            {
                productFile << e.first << " " << e.second << endl;
            }
        }
        else
        {
            cerr << "Error opening product file" << endl;
        }
    }

    void write_info() override
    {
        string product, price;

        cout << "Please write your product: ";
        cin >> product;

        cout << "Please write your price: ";
        cin >> price;

        user_products_information.push_back({product, price});
    }
};

int main()
{
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

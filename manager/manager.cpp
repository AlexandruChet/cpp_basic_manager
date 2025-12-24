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
    vector<string> user_products_information;

    User() : Entity("", "", 0, 0) {}

    void registration() override
    {
        cout << "Please write your name: ";
        cin >> name;

        cout << "Please write your email: ";
        cin >> email;

        srand(time(nullptr));
        id = rand();

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
                else if (holds_alternative<string>(element))
                    outFile << get<string>(element) << " ";
            }
        }
        else
        {
            cerr << "Error" << endl;
        }
    }
    void save_info_to_file() override {}
    void write_info() override {}
};

int main()
{
    Entity *user = new User();
    user->registration();
    user->save_to_file();

    delete user;
    return 0;
}

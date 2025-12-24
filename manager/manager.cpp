#include <iostream>
#include <string>
#include <vector>
#include <variant>
#include <ctime>
#include <cstdlib>

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
    }

    void save_to_file() override {}
    void save_info_to_file() override {}
    void write_info() override {}
};

int main()
{
    Entity* user = new User();
    user->registration();

    delete user;
    return 0;
}

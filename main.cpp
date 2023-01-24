#include <iostream>
#include "class.h"

using namespace ns;

int dialog (const char *what[]) {
    const char *errmess = "Incorrect value\nTry Again";
    int choose = 0;
    for (int i = 0; i < 7; i++)
        cout << what[i] << endl;
    do {
        enter(choose, "Enter your choose:");
        if (choose <= 0 || choose > 7)
            cout << errmess << endl;
        else break;
    } while (1);
    if (choose == 7)
        return -1;
    return choose;
}

void show_vector( std::vector<AbstractPocket *>&a)
{
    for (auto & it : a)
        cout << it;
}

void print_info (const Info& a) {
    cout << a.version << endl;
    cout << a.name << endl;
    cout << a.count_relation << endl;
    cout << a.last_version << endl;
    cout << a.download << endl;
}

int menu(int choose, AbstractPocket * pocket_temp, PocketManager manager) {
    std::vector<AbstractPocket *> vector_new;
    std::vector<AbstractPocket *> vector_temp;
    int choose2;
    bool downloaded = false;
    string name;
    int last;
    int version;
    string pub_name;
    Info info;
    if (choose == -1)
        return -1;
    switch (choose) {
        case 1:
            cout << "Ok. Now we need to create new pocket" << endl;
            enter(name, "Enter the name of your pocket");
            enter(last, "Enter the last version of pocket " + name);
            enter (version, "Enter the version of pocket" + name);
            enter (pub_name, "Enter the name of publisher");
            pocket_temp = new Pocket(false, "pocket", 2, 1, "name", vector_new);
            vector_temp.push_back(pocket_temp);
            manager.add_to_map((Pocket *) pocket_temp);
            info = ((Pocket *) pocket_temp)->get_info();
            print_info(info);
            break;
        case 2:
            enter(name, "Enter the name of your pocket");
            info = ((Pocket *) pocket_temp)->get_info();
            print_info(info);
            break;
        case 3:
            enter(name, "Enter the name of your pocket");
            ((Pocket *)pocket_temp)->delete_from_library(&manager);
            cout << "Pocket was deleted from library";
            break;
        case 4:
            enter(name, "Enter the name of your pocket");
            ((Pocket *)pocket_temp)->update();
            cout << "Pocket was updated to the last version";
            break;
        case 5:
            enter(name, "Enter the name of your pocket");
            enter(choose2, "1. Silent install\n2. Classic install");
            switch(choose2) {
                case 1:
                    manager.installation(name);
                case 2:
                    manager.installation_ask_access(name);
            }
            break;
        case 6:
            manager.system_clear();
            break;
        default:
            return 0;
    }
    return 0;
}

int main () {
    const char *what[] = {"1. Add new pocket to the Library", "2. Get type of the pocket", "3. Delete pocket",
                          "4. Update pocket", "5. Install pockets",
                          "6. System clear", "7. Exit"};
    int flag;
    AbstractPocket * pocket_temp = nullptr;
    std::vector<AbstractPocket *> vector_new;
    PocketManager manager(vector_new);
    do {
        flag = menu(dialog(what), pocket_temp, manager);
        if (flag == -1)
            return 0;
    } while (1);
}

#ifndef UNTITLED14_CLASS_H
#define UNTITLED14_CLASS_H
#include <iostream>
#include <string>
#include <vector>
#include <map>

namespace ns {
    using std::cin;
    using std::cout;
    using std::endl;
    using std::bad_alloc;
    using std::string;

    struct Info {
        bool download;
        std::string name;
        int last_version;
        int version;
        int count_relation;
    };

    class AbstractPocket {
    private:

    public:
        virtual int get_type() = 0;
        virtual std::string get_name() = 0;
        virtual std::vector<AbstractPocket *> get_dependency () = 0;
        virtual int is_download() = 0;
        virtual int set_download() = 0;
        virtual int set_not_download() = 0;
    };

    class Pocket_free : public AbstractPocket {
    private:
        AbstractPocket *pocket;
    public:
        explicit Pocket_free(AbstractPocket *indx) : pocket(indx) {};
        int get_type() override { return 1; };
        std::string get_name() override {return pocket->get_name();};
        std::vector<AbstractPocket *> get_dependency() override {return pocket->get_dependency();}
        int is_download () override {return pocket->is_download();};
        int set_download() override {pocket->set_download(); return 0;};
        int set_not_download() override {pocket->set_not_download(); return 0;}
    };

    class PocketManager;

    class Pocket : public AbstractPocket {
    private:
        bool download{};
        std::string name;
        int last_version{};
        int version{};
        std::string publisher_name;
        std::vector<AbstractPocket *> dependency;
    public:
        explicit Pocket(bool dow, const std::string &name, int last_ver, int ver, const std::string &pub_name,
                        std::vector<AbstractPocket *> &poc);

        Info get_info();
        int update();
        std::string get_name() override { return name;};
        int get_type() override { return 2; };
        std::vector<AbstractPocket *> get_dependency() override {return dependency;};
        int is_download() override {return download;};
        int set_download() override {download = true; return 0;};
        int set_not_download() override {download = false; return 0;};
        int add_to_library (PocketManager *manager);
        int delete_from_library(PocketManager *manager);
    };

    class PocketLibrary : Pocket {
    private:
        int count_of_dependency;
    public:
        int get_type() override { return 3; };
        int plus_count () {count_of_dependency++; return 0;};
        int minus_count ();
        int get_count_of_dependency() const {return count_of_dependency;};
    };

    class PocketManager {
    private:
        std::map<std::string, AbstractPocket *> manager;
    public:
        explicit PocketManager(std::vector<AbstractPocket *> vec);

        int installation (const std::string& name);
        int installation_ask_access (const std::string& name);
        int delete_pocket (const std::string& name);
        int system_clear ();
        int system_update ();
        int add_to_map(Pocket *pocket);
        int delete_from_map(Pocket *pocket);
    };

    template<class T>
    int enter(T &a, const string &what) {
        cout << what << endl;
        cin >> a;
        if (!cin.good()) {
            cout << "Error with cin \n Try again" << endl;
            return 1;
        } else
            return 0;
    }
}

#endif //UNTITLED14_CLASS_H

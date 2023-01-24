#ifndef UNTITLED14_CLASS_H
#define UNTITLED14_CLASS_H
#include <iostream>
#include <string>
#include <vector>
#include <map>

/** \file
 * \brief Файл с классами пакетов и пакетного менеджера
 */

namespace ns {
    using std::cin;
    using std::cout;
    using std::endl;
    using std::bad_alloc;
    using std::string;

    /// Структура, описывающая получаемую от пакета информацию
    struct Info {
        bool download;
        std::string name;
        int last_version;
        int version;
        int count_relation;
    };

    /// Класс, описывающий абстрактный пакет
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

    /// Класс, описывающий пустой пакет
    class Pocket_free : public AbstractPocket {
    private:
        AbstractPocket *pocket;
    public:
        explicit Pocket_free(AbstractPocket *indx) : pocket(indx) {};
        /// Функция возвращающая тип
        int get_type() override { return 1; };
        /// Функция, возвращающая имя пакета
        std::string get_name() override {return pocket->get_name();};
        /// Функция зависимости
        /**
         * Возвращает вектор из указателей на абстрактный пакет, который состоит из зависимых пакетов.
         */
        std::vector<AbstractPocket *> get_dependency() override {return pocket->get_dependency();}
        /// Функция, проверяющая, скачен ли пакет
        int is_download () override {return pocket->is_download();};
        /// Функция, устанавливающая пакет
        int set_download() override {pocket->set_download(); return 0;};
        /// Функция, удаляющая пакет
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
        /// Функция, обновляющая пакет
        int update();
        /// Функция, которая возвращает имя пакета
        std::string get_name() override { return name;};
        /// Функция, которая возвращает тип пакета
        int get_type() override { return 2; };
        std::vector<AbstractPocket *> get_dependency() override {return dependency;};
        int is_download() override {return download;};
        int set_download() override {download = true; return 0;};
        int set_not_download() override {download = false; return 0;};
        /// Добавление в библиотеку
        /**
         * Добавляет конкретный пакет в библиотеку. Принимает указатель на менеджер пакетов.
         */
        int add_to_library (PocketManager *manager);
        /// Удаление из библиотеки
        /**
         * Удаляет конкретный пакет из библиотеки. Принимает указатель на менеджер пакетов.
         */
        int delete_from_library(PocketManager *manager);
    };

    /// Класс пакета со вспомогательным ПО
    class PocketLibrary : Pocket {
    private:
        /// Переменная, отвечающая за количество зависимых пакетов
        int count_of_dependency;
    public:
        int get_type() override { return 3; };
        /// Функция, добавляющая один зависимый пакет
        int plus_count () {count_of_dependency++; return 0;};
        /// Функция, удаляющая один зависимый пакет
        int minus_count ();
        /// Функция, возвращающая количество зависимых пакетов
        int get_count_of_dependency() const {return count_of_dependency;};
    };

    /// Класс пакетного менеджера
    class PocketManager {
    private:
        /// Вектор - библиотека
        std::map<std::string, AbstractPocket *> manager;
    public:
        explicit PocketManager(std::vector<AbstractPocket *> vec);

        /// Функция тихой установки
        /**
         * Скачивает пакет по имени без запроса у пользователя.
         */
        int installation (const std::string& name);
        /// Функция установки с запросом
        /**
         * Скачивает пакет по имени, устанавливая каждый пакет с запросом у пользователя.
         */
        int installation_ask_access (const std::string& name);
        /// Функция удаления пакета из хранилища
        int delete_pocket (const std::string& name);
        /// Функция очистки системы
        /**
         * Происходит очистка системы от неиспользуемых вспомогательных пакетов.
         */
        int system_clear ();
        /// Функция глобального обновления системы
        /**
         * Производит глобальное обновление системы с выводом данных о каждом обновленном пакете.
         */
        int system_update ();
        /// Функция добавления пакета в мап
        int add_to_map(Pocket *pocket);
        /// Функция удаления пакета из мап
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

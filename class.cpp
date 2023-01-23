#include "class.h"
#include <iostream>
#include <string>
#include <vector>

using namespace ns;

Pocket::Pocket(bool dow, const std::string &na, int last_ver, int ver, const std::string &pub_name,
               std::vector<AbstractPocket *> &poc) {
    download = dow;
    name = na;
    last_version = last_ver;
    publisher_name = pub_name;
    dependency = poc;
}

Info Pocket::get_info() {
    Info inf;
    inf.name = name;
    inf.version = version;
    inf.download = download;
    inf.last_version = last_version;
    inf.count_relation = dependency.size();
    return inf;
}

int Pocket::update() {
    version = last_version;
    return 0;
}

int PocketLibrary::minus_count() {
    if (count_of_dependency == 0)
        return 1;
    count_of_dependency--;
    return 0;
}

PocketManager::PocketManager(std::vector<AbstractPocket *> vec) {
    for (auto e : vec) manager[e->get_name()] = e;
}

int PocketManager::installation(const std::string& name) {
    if (manager[name]->get_type() == 3)
        ((PocketLibrary *) manager[name])->plus_count();
    if (manager[name]->is_download() == true)
        return 1;
    auto dependency = manager[name]->get_dependency();
    for (auto e : dependency) installation(e->get_name());
    manager[name]->set_download();
    return 0;
}

int PocketManager::delete_pocket(const std::string &name) {
    int count_of_deleted = 0;
    if (manager[name]->get_type() == 3) {
        ((PocketLibrary *) manager[name])->minus_count();
        if (((PocketLibrary *) manager[name])->get_count_of_dependency() != 0)
            return 0;
    }
    if (manager[name]->is_download() != true)
        return 0;
    auto dependency = manager[name]->get_dependency();
    for (auto e : dependency) count_of_deleted+= delete_pocket(e->get_name());
    manager[name]->set_not_download();
    return count_of_deleted;
}

int PocketManager::system_clear() {
    int count_of_deleted = 0;
    for (auto e : manager) {
        if (manager[e.second->get_name()]->get_type() == 3) {
            if (((PocketLibrary *) manager[e.second->get_name()])->get_count_of_dependency() == 0)
                count_of_deleted += delete_pocket(e.second->get_name());
        }
    }
    return count_of_deleted;
}

int PocketManager::system_update() {
    for (auto e : manager) {
        if (manager[e.second->get_name()]->get_type() == 2) {
            ((Pocket *) manager[e.second->get_name()])->update();
        }
    }
    return 0;
}

int PocketManager::installation_ask_access(const std::string &name) {
    int choose = 0;
    if (manager[name]->get_type() == 3)
        ((PocketLibrary *) manager[name])->plus_count();
    if (manager[name]->is_download() == true)
        return 1;
    auto dependency = manager[name]->get_dependency();
    for (auto e : dependency) {
        std::cout << "Do you want to install pocket " << std::endl;
        enter(choose, "Do you want to install pocket " + name + "?\n1 - yes\n2 - no");
        if (choose == 0)
            return 0;
        installation(e->get_name());
    }
    manager[name]->set_download();
    return 0;
}

int PocketManager::add_to_map(Pocket *pocket) {
    manager[pocket->get_name()] = pocket;
    return 0;
}

int PocketManager::delete_from_map(Pocket *pocket) {
    manager.erase(pocket->get_name());
    return 0;
}

int Pocket::add_to_library(PocketManager *manager) {
    manager->add_to_map(this);
    return 0;
}

int Pocket::delete_from_library(PocketManager *manager) {
    manager->delete_from_map(this);
    return 0;
}

#include "gtest/gtest.h"
#include "inclass.h"
#include <string>
#include <iostream>

using namespace ns;
using namespace std;

TEST(Constructor, Pocket) {
    std::vector<AbstractPocket *> vector;
    Pocket pocket(false, "pocket", 1, 1, "name", vector);
    Info info = pocket.get_info();
    ASSERT_EQ(info.download, false);
    ASSERT_EQ(info.last_version, 2);
    ASSERT_EQ(info.version, 1);
    ASSERT_EQ(info.count_relation, 0);
    ASSERT_EQ(info.name, "pocket");
}

TEST(Methods, Pocket) {
    std::vector<AbstractPocket *> vector;
    Pocket pocket(false, "pocket", 2, 1, "name", vector);
    Info info = pocket.get_info();
    ASSERT_EQ(info.download, false);
    ASSERT_EQ(info.last_version, 2);
    ASSERT_EQ(info.version, 1);
    ASSERT_EQ(info.count_relation, 0);
    ASSERT_EQ(info.name, "pocket");
    pocket.update();
    info = pocket.get_info();
    ASSERT_EQ(info.version, 2);
    ASSERT_EQ(pocket.is_download(), false);
    pocket.set_download();
    ASSERT_EQ(pocket.is_download(), true);
    pocket.set_not_download();
    ASSERT_EQ(pocket.is_download(), false);
    ASSERT_EQ(pocket.get_type(), 2);
}

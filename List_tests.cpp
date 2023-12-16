// Project UID c1f28c309e55405daf00c565d57ff9ad

#include "List.h"
#include "unit_test_framework.h"
#include <cassert>

using namespace std;

TEST(test_empty)
{
    List<int> list;
    ASSERT_TRUE(list.empty());
    list.push_front(3);
    ASSERT_FALSE(list.empty());
}

TEST(test_size)
{
    List<int> list;
    ASSERT_EQUAL(list.size(), 0);
    list.push_front(3);
    list.push_front(2);
    ASSERT_EQUAL(list.size(), 2);
}

TEST(test_front)
{
    List<int> list;
    list.push_front(9);
    ASSERT_EQUAL(list.front(), 9);
    list.push_front(7);
    ASSERT_EQUAL(list.front(), 7);
    list.pop_front();
    ASSERT_EQUAL(list.front(), 9);
}

TEST(test_back)
{
    List<int> list;
    list.push_front(8);
    ASSERT_EQUAL(list.back(), 8);
    list.push_front(5);
    list.push_front(3);
    list.push_back(7);
    ASSERT_EQUAL(list.back(), 7);
    list.pop_back();
    ASSERT_EQUAL(list.back(), 8);
}

TEST(test_clear)
{
    List<int> list;
    list.push_front(8);
    list.push_front(5);
    list.push_front(3);
    list.push_back(7);
    ASSERT_FALSE(list.empty());
    list.clear();
    ASSERT_TRUE(list.empty());
}

TEST(test_copy_ctr)
{
    List<int> list;
    list.push_front(8);
    list.push_front(5);
    list.push_front(3);
    List<int> copy(list);
    List<int>::Iterator i(list.begin());
    List<int>::Iterator j(copy.begin());
    ASSERT_EQUAL(*i, *j);
    ++i;
    ++j;
    ASSERT_EQUAL(*i,*j);
    ++i;
    ++j;
    ASSERT_EQUAL(*i,*j);
    List<int>::Iterator k;
    k = list.begin();
    ASSERT_EQUAL(*k, 3);

}

TEST(test_insert_front)
{
    List<int> list;
    list.push_front(8);
    list.push_front(5);
    list.insert(list.begin(), 3);
    ASSERT_EQUAL(list.front(), 3);
}
TEST(test_insert_mid)
{
    List<int> list;
    list.push_front(8);
    list.push_front(5);
    list.push_front(9);
    list.push_front(7);
    list.insert(++list.begin(), 3);
    list.pop_front();
    ASSERT_EQUAL(list.front(), 3);
}
TEST(test_insert_back)
{
    List<int> list;
    list.push_front(8);
    list.push_front(5);
    list.insert(list.end(), 7);
    ASSERT_EQUAL(list.back(), 7);
}

TEST(test_erase_front)
{
    List<int> list;
    list.push_front(8);
    list.push_front(5);
    ASSERT_EQUAL(list.front(), 5);
    list.erase(list.begin());
    ASSERT_EQUAL(list.front(), 8);
}

TEST(test_erase_mid)
{
    List<int> list;
    list.push_front(4);
    list.push_front(5);
    list.push_front(6);
    list.push_front(9);
    list.erase(++list.begin());
    list.pop_front();
    ASSERT_EQUAL(list.front(), 5);
}
TEST(test_erase_back)
{
    List<int> list;
    list.push_front(4);
    list.push_front(5);
    list.push_front(6);
    list.push_front(9);
    ASSERT_EQUAL(list.back(), 4);
    List<int>::Iterator i = list.begin();
    ++i;
    ++i;
    ++i;
    list.erase(i);
    ASSERT_EQUAL(list.back(), 5);
}


TEST(test_equals_operator)
{
    List<int> listy;
    listy.push_front(4);
    listy.push_front(5);
    listy.push_front(6);

    List<int> lister;
    lister = listy;
    ASSERT_EQUAL(listy.back(), lister.back());
    ASSERT_EQUAL(listy.front(), lister.front());
    ASSERT_EQUAL(*(++listy.begin()), *(++lister.begin()));
    List<int> another;
    another.push_back(3);
    another.push_back(4);
    another.push_front(2);
    listy = another;

}

TEST(test_push_back)
{
    List<int> list;
    list.push_back(5);
    ASSERT_EQUAL(list.front(), 5);
    list.push_back(7);
    ASSERT_EQUAL(list.back(), 7);

    List<int>::Iterator i(list.begin());
    List<int>::Iterator j(list.begin());

}

TEST(test_urmom)
{
    List<int> list;
    List<int> listy;
    list.push_back(4);
    list.push_back(3);
    listy.push_front(12);
    listy.push_back(4);

    List<int>::Iterator i(list.begin());
    List<int>::Iterator j(listy.begin());
    List<int>::Iterator k(list.end());
    List<int>::Iterator l(listy.end());
    ++i;
    ++j;
    assert(i != j);
    assert(k == l);
    assert(i != j);
}

TEST(test_pop_front)
{
    List<int> list;
    list.push_back(4);
    list.pop_front();
    assert(list.empty());
    list.push_back(5);
    list.push_back(6);
    list.pop_front();
    ASSERT_EQUAL(*list.begin(), 6);
    list.push_back(7);
}

TEST(test_pop_back)
{
    List<int> list;
    list.push_back(4);
    list.pop_back();
    assert(list.empty());
    list.push_back(5);
    list.push_back(6);
    list.push_back(7);
    List<int>::Iterator i(list.begin());
    ++i;
    ++i;
    ASSERT_EQUAL(*i, 7);
    list.pop_back();
    ASSERT_EQUAL(list.back(), 6);
}


TEST_MAIN()

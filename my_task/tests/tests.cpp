// my_sin.cpp: определяет точку входа для приложения.
//

#include <gtest/gtest.h>
#include "task.h"
#include "ft.h"


using namespace testspace;

TEST(task_lib_test, size8)
{
    std::vector<std::complex< double >>
        vect{ {0.0, 0.0 }, {1.0, 0.0}, {2, 0.0}, {3.0, 0.0},
            {4.0, 0.0}, {5, 0.0}, {6.0, 0.0} , {7.0, 0.0} };

    std::vector<std::complex< double >> res = myfft(vect);
    std::vector<std::complex< double >> true_res = fur(vect);


    double  diff_res = 0;
    for (size_t i = 0; i < vect.size(); i++) {
        diff_res += abs(res[i] - true_res[i]);
    }

    ASSERT_NEAR(diff_res, 0, 0.0001);
}
TEST(task_lib_test, size6)
{
    std::vector<std::complex< double >>
        vect{ {0.0, 0.0 }, {1.0, 67.0}, {2, 98.0}, {36.0, 0.0},
              {4.0, 6.0 }, {5, 12.0},};

    std::vector<std::complex< double >> res = myfft(vect);
    std::vector<std::complex< double >> true_res = fur(vect);


    double  diff_res = 0;
    for (size_t i = 0; i < vect.size(); i++) {
        diff_res += abs(res[i] - true_res[i]);
    }

    ASSERT_NEAR(diff_res, 0, 0.0001);
}
TEST(task_lib_test, size16)
{
    std::vector<std::complex< double >>
        vect{ {0.0, 123.0 }, {1.0, 0.0}, {2, 0.0}, {45.0, 0.0},
              {44.0, 54.0},  {5, 0.0},  {6.0, 0.0} , {7.0, 24.0},
              {121.0, 0.0 }, {1.0, 0.0}, {2, 0.0}, {36.0, 9.0},
              {4.0, 0.0}, {75, 0.0}, {6.0, 80.0} , {77.0, 0.0} };

    std::vector<std::complex< double >> res = myfft(vect);
    std::vector<std::complex< double >> true_res = fur(vect);


    double  diff_res = 0;
    for (size_t i = 0; i < vect.size(); i++) {
        diff_res += abs(res[i] - true_res[i]);
    }

    ASSERT_NEAR(diff_res, 0, 0.0001);
}
TEST(task_lib_test, size12)
{
    std::vector<std::complex< double >>
        vect{ {0.432, 123.0 }, {1.0, 123.0}, {2, 0.0}, {45.0, 0.0},
              {124.0, 54.0},  {5, 0.0},  {6.0, 65.0} , {47.0, 255.0},
              {121.0, 0.0 }, {1.0, 0.0}, {245, 123.0}, {36.0, 9.0} };

    std::vector<std::complex< double >> res = myfft(vect);
    std::vector<std::complex< double >> true_res = fur(vect);


    double  diff_res = 0;
    for (size_t i = 0; i < vect.size(); i++) {
        diff_res += abs(res[i] - true_res[i]);
    }

    ASSERT_NEAR(diff_res, 0, 0.0001);
}
int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
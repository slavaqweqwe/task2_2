// my_sin.cpp: определяет точку входа для приложения.
//

#include <gtest/gtest.h>
#include "task.h"
std::vector<std::complex< double >> fur(std::vector<std::complex< double >> vect) {
    std::vector<std::complex< double >> outVect(vect.size());
    std::complex< double > comp_one(0, 1.0);
    for (size_t j = 0; j < vect.size(); j++) {
        for (size_t i = 0; i < vect.size(); i++) {
            outVect[j] += vect[i] * exp(comp_one * ((-2 * PI * i * j) / vect.size()));

        }
    }
    return outVect;
}
using namespace testspace;

TEST(task_lib_test, size8)
{
    std::vector<std::complex< double >>
        vect{ std::complex<double>(0.0, 0.0), std::complex<double>(1.0, 0.0), std::complex<double>(2, 0.0),
              std::complex<double>(3.0, 0.0), std::complex<double>(4.0, 0.0), std::complex<double>(5, 0.0),
              std::complex<double>(6.0, 0.0) ,std::complex<double>(7.0, 0.0) };

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
        vect{ std::complex<double>(0.5, 8.0), std::complex<double>(1.0, 67.0), std::complex<double>(25, 3234.0),
              std::complex<double>(36.0, 0.0), std::complex<double>(67.0, 0.0), std::complex<double>(5, 9.0)};

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
        vect{ std::complex<double>(0.0, 0.0), std::complex<double>(1.0, 0.0), std::complex<double>(2, 0.0),
              std::complex<double>(3.0, 0.0), std::complex<double>(4.0, 0.0), std::complex<double>(5, 0.0),
              std::complex<double>(6.0, 0.0) ,std::complex<double>(7.0, 0.0), 
              std::complex<double>(0.0, 0.0), std::complex<double>(123.0, 1231.0), std::complex<double>(2, 0.0),
              std::complex<double>(3.0, 2323.0), std::complex<double>(242.0, 0.0), std::complex<double>(5, 546.0),
              std::complex<double>(6.0, 123.0) ,std::complex<double>(7.0, 232.0) };

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
        vect{ std::complex<double>(0.0, 0.0), std::complex<double>(1.0, 0.0), std::complex<double>(2, 0.0),
              std::complex<double>(3.0, 0.0), std::complex<double>(4.0, 0.0), std::complex<double>(5, 0.0),
              std::complex<double>(6.0, 0.0) ,std::complex<double>(7.0, 0.0),
              std::complex<double>(576.0, 98.0), std::complex<double>(123.0, 1231.0), std::complex<double>(2, 0.0),
              std::complex<double>(3.0, 233.0) };

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
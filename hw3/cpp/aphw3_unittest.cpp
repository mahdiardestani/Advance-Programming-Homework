#include "aphw3.h"
#include "gtest/gtest.h"
#include <iomanip>
#include <iostream>
#include <limits.h>
#include <vector>
namespace {
TEST(APHW3Test, DatasetTest)
{
    Dataset ds { loadFuncDataset("APHW3Data1.csv") };
    size_t no { ds.getNoOfSamples() };
    size_t train_no { ds.getNoOfTrainSamples() };
    size_t test_no { ds.getNoOfTestSamples() };
    EXPECT_EQ(40, no);
    EXPECT_EQ(28, train_no);
    EXPECT_EQ(12, test_no);
    EXPECT_EQ(0., ds.getTargets()[0][0]);
    EXPECT_EQ(-2, ds.getInputs()[0][0]);
    std::cout << "---- test------" << std::endl;
    // EXPECT_TRUE(ds[10][1][0][0] > 0.29 && ds[10][1][0][0] < 0.3); -> I cant undestand this
    double a { ds.getTrainInputs()[0][0] };
    ds.shuffle();
    double b { ds.getTrainInputs()[0][0] };
    ds.shuffle();
    double c { ds.getTrainInputs()[0][0] };
    EXPECT_TRUE(a != b || a != c);
    Dataset ds1 { ds + ds };
    EXPECT_EQ(80, ds1.getNoOfSamples());
}
TEST(APHW3Test, NeuralNetFPTest)
{
    Dataset ds { loadFuncDataset("APHW3Data1.csv") };
    ds.shuffle();
    NeuralNet nn { ds, 2 };
    Matrix p { 1, 1 };
    Matrix w1 { 2, 1 }, w2 { 1, 2 }, b1 { 2, 1 }, b2 { 1, 1 };
    b1[0][0] = -0.48;
    b1[1][0] = -0.13;
    w1[0][0] = -0.27;
    w1[1][0] = -0.41;
    b2[0][0] = 0.48;
    w2[0][0] = 0.09;
    w2[0][1] = -0.17;
    nn.setW1(w1);
    nn.setW2(w2);
    nn.setB1(b1);
    nn.setB2(b2);
    Matrix fp { nn.forwardPropagate(p) };
    fp.show();
    EXPECT_TRUE(fp[0][0] > 0.43 && fp[0][0] < 0.44);
}
TEST(APHW3Test, NeuralNetFitTest)
{
    Dataset ds { loadFuncDataset("APHW3Data1.csv") };
    ds.shuffle();
    NeuralNet nn { ds, 2 };
    Matrix p { 1, 1 };
    Matrix w1 { 2, 1 }, w2 { 1, 2 }, b1 { 2, 1 }, b2 { 1, 1 };
    b1[0][0] = -.48;
    b1[1][0] = -0.13;
    w1[0][0] = -.27;
    w1[1][0] = -0.41;
    b2[0][0] = 0.48;
    w2[0][0] = 0.09;
    w2[0][1] = -0.17;
    nn.setW1(w1);
    nn.setW2(w2);
    nn.setB1(b1);
    nn.setB2(b2);
    Matrix fp { nn.forwardPropagate(p) };

    Result r { nn.fit() };
    EXPECT_TRUE(r.getTestLoss() < 1);
    std::cout << "Result of Neural Network: " << std::endl;
    std::cout << r << std::endl;
}
TEST(APHW3Test, ResultTest)
{
    Result r1(0.1, 0.4, 5);
    Result r2(0.2, 0.3, 5);
    EXPECT_TRUE(r2 < r1);
}
TEST(APHW3Test, SumTest)
{
    std::vector<std::vector<double>> data;
    data.push_back(std::vector<double> { 2, 4 });
    data.push_back(std::vector<double> { 6, 7 });
    Matrix a(data);
    Matrix b(data);
    Matrix c = a + b;
    EXPECT_EQ(12, c[1][0]);
}
}

#include "gtest/gtest.h"
#include "../cppca.h"

TEST(CaBaseTest, CaZeros) {
  CA ca(100, 100);
  for(int r=0;r<100;r++) 
    for(int c=0;c<100;c++)
      EXPECT_EQ(0, ca.get_cell(r, c));
}

TEST(CaLifeTest, ThreeLineOK) {
  CALife ca(5, 5);
  ca.set_cell(1, 2, 1);
  ca.set_cell(2, 2, 1);
  ca.set_cell(3, 2, 1);

  ca.update();

  EXPECT_EQ(3, ca.sum_state());
}

TEST(CaLifeTest, TestGlider) {
  CALife ca(10, 10);

  ca.set_cell(5, 5, 1);
  ca.set_cell(5, 4, 1);
  ca.set_cell(5, 6, 1);
  ca.set_cell(4, 6, 1);
  ca.set_cell(3, 5, 1);

  for (int i=0; i<150; i++) {
    ca.update();
    EXPECT_EQ(5, ca.sum_state());
  }
}


int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

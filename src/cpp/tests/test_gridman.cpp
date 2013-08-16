#include "gtest/gtest.h"
#include "../gridmanager.h"

TEST(GridRef, Equality) {
  GridRef a(1,2), b(1, 2);

  EXPECT_EQ(a, b);
}

TEST(GridRef, OperatorPlus) {
  GridRef a(1, 2), b(3, 4);

  EXPECT_EQ(a + b, GridRef(4, 6));
}

TEST(GridManager, Constructor) {
  GridManager gm(4000, 4000, 4);

  EXPECT_EQ(16000000, gm.TotalCells());
}

TEST(GridManager, SetDimensions) {
  GridManager gm(4000, 4000, 4);
  
  GridRef gr = gm.GridDimensions();

  EXPECT_EQ(2, gr.r);
  EXPECT_EQ(2, gr.c);
}

TEST(GridManager, TilePosition) {
  GridManager gm(4000, 4000, 4);

  GridRef gr = gm.TilePosition(2);

  EXPECT_EQ(1, gr.r);
  EXPECT_EQ(0, gr.c);
}

TEST(GridManager, TileSID) {
  GridManager gm(4000, 4000, 6);

  for(int i = 0; i < 10; i++) {
    EXPECT_EQ(i, gm.TileSID(gm.TilePosition(i)));
  }
}


int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

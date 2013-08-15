#include "gtest/gtest.h"
#include "../gridmanager.h"


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

int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

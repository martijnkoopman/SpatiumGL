#include <gtest/gtest.h>
#include <thread>

TEST(System, sizeofs)
{
  EXPECT_EQ(1, sizeof(char));
  EXPECT_EQ(2, sizeof(short int));
  EXPECT_EQ(4, sizeof(int));
  EXPECT_EQ(4, sizeof(long int));
  EXPECT_EQ(8, sizeof(long long int));
  EXPECT_EQ(4, sizeof(float));
  EXPECT_EQ(8, sizeof(double));
}

TEST(System, endianess)
{
  unsigned int i = 1;
  unsigned char* c = reinterpret_cast<unsigned char*>(&i);
  bool bigEndian = (*c == 0);
}
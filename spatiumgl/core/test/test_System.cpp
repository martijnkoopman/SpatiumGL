#include <gtest/gtest.h>
#include <thread>

TEST(System, sizeofs)
{
  EXPECT_EQ(1, sizeof(char));
  EXPECT_EQ(2, sizeof(short int));
  EXPECT_EQ(4, sizeof(int));
  // long int = 4 bytes on Windows (LLP64)
  // long int = 8 bytes on Unix (LP64)
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

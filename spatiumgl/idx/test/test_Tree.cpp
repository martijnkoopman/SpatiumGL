#include <gtest/gtest.h>

#include <spatiumgl/idx/NTree.hpp>
#include <spatiumgl/idx/Octree.hpp>

TEST(Tree, NQuadtree)
{
  spgl::idx::NTree<4> quadtree;
  spgl::idx::NTreeNode<4>* node = quadtree.root();

  EXPECT_TRUE(node->child(0) == nullptr);
  EXPECT_EQ(node->createChild(0), true);
  EXPECT_TRUE(node->child(0) != nullptr);
  EXPECT_EQ(node->createChild(0), false);
  EXPECT_EQ(node->deleteChild(0), true);
  EXPECT_TRUE(node->child(0) == nullptr);
  EXPECT_EQ(node->deleteChild(0), false);
}

TEST(Tree, NOctree)
{
  spgl::idx::NTree<8> octree;
  spgl::idx::NTreeNode<8>* node = octree.root();

  EXPECT_TRUE(node->child(0) == nullptr);
  EXPECT_EQ(node->createChild(0), true);
  EXPECT_TRUE(node->child(0) != nullptr);
  EXPECT_EQ(node->createChild(0), false);
  EXPECT_EQ(node->deleteChild(0), true);
  EXPECT_TRUE(node->child(0) == nullptr);
  EXPECT_EQ(node->deleteChild(0), false);
}

TEST(Tree, ReadWriteOctree) {
  // Construct a tree
  spgl::idx::Octree octreeOut({});
  spgl::idx::OctreeNode* node = octreeOut.root();
  node->createChild(0);
  node->createChild(2);
  node->createChild(4);
  node->createChild(6);
  node->createChild(7);
  node->child(6)->createChild(0);
  node->child(6)->createChild(1);
  node->child(6)->createChild(2);
  node->child(6)->createChild(3);

  // Write to file
  EXPECT_GT(spgl::idx::Octree::writeToFile(octreeOut, "octree.idx"), 0);

  // Read from file
  spgl::idx::Octree octreeIn({});
  EXPECT_TRUE(spgl::idx::Octree::readFromFile("octree.idx", octreeIn));

  // Compare octrees
  EXPECT_TRUE(octreeIn.root() != nullptr);
  EXPECT_TRUE(octreeIn.root()->child(0) != nullptr);
  EXPECT_TRUE(octreeIn.root()->child(1) == nullptr);
  EXPECT_TRUE(octreeIn.root()->child(2) != nullptr);
  EXPECT_TRUE(octreeIn.root()->child(3) == nullptr);
  EXPECT_TRUE(octreeIn.root()->child(4) != nullptr);
  EXPECT_TRUE(octreeIn.root()->child(5) == nullptr);
  EXPECT_TRUE(octreeIn.root()->child(6) != nullptr);
  EXPECT_TRUE(octreeIn.root()->child(7) != nullptr);
  EXPECT_TRUE(octreeIn.root()->child(6)->child(0) != nullptr);
  EXPECT_TRUE(octreeIn.root()->child(6)->child(1) != nullptr);
  EXPECT_TRUE(octreeIn.root()->child(6)->child(2) != nullptr);
  EXPECT_TRUE(octreeIn.root()->child(6)->child(3) != nullptr);
  EXPECT_TRUE(octreeIn.root()->child(6)->child(4) == nullptr);
  EXPECT_TRUE(octreeIn.root()->child(6)->child(5) == nullptr);
  EXPECT_TRUE(octreeIn.root()->child(6)->child(6) == nullptr);
  EXPECT_TRUE(octreeIn.root()->child(6)->child(7) == nullptr);
}
/*
 * Program: Spatium Graphics Library
 *
 * Copyright (C) Martijn Koopman
 * All Rights Reserved
 *
 * This software is distributed WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.
 *
 */

#ifndef SPATIUMGL_IDX_OCTREE_H
#define SPATIUMGL_IDX_OCTREE_H

#include "spatiumgl/idx/NTree.hpp"

#include <fstream> // std::ofstream, std::ifstream
#include <queue>   // std::queue
#include <cstring> // std::memcmp

namespace spgl {
namespace idx {

class SPATIUMGL_EXPORT Octree : public NTree<8>
{
public:
  Octree(const BoundingCube& bounds)
    : m_bounds(bounds)
  {}

  /// Get bounds of entire octree. (cubical)
  ///
  /// \return Bounds
  const BoundingCube& bounds() const { return m_bounds; }

  /// Compute child bounds.
  ///
  /// \param[in] parentBounds Bounds of parent node
  /// \param[in] childIndex Child index (0-7)
  /// \return Child bounds.
  static BoundingCube computeChildBounds(const BoundingCube& parentBounds,
                                         size_t childIndex);

  /// Write octree to file.
  ///
  /// File format:
  /// 1. ASCII signature: SPATIUMGL_OCTREE\n
  /// 2. Extent: Xmin, Ymin, Zmin, Xmax, Ymax, Zmax (64-bit floating points)
  /// 3. Nodes: 1 byte (8 bits) per node. 1 bit for each child.
  static size_t writeToFile(const Octree& octree, const std::string& fileName)
  {
    size_t bytesWritten = 0;
    std::ofstream ofile(fileName, std::ios::out | std::ios::binary);
    if (!ofile.is_open()) {
      return bytesWritten;
    }

    ofile.write("SPATIUMGL_OCTREE\n", 17);
    bytesWritten += 17;
    // xmin, ymin, zmin
    // xmax, ymax, zmax

    std::queue<const OctreeNode*> queue;
    queue.push(octree.root());
    while (!queue.empty()) {
      // Pop front of queue
      const OctreeNode* node = queue.front();
      queue.pop();

      // Iterate children
      unsigned char bits = 0x00;
      for (unsigned char i = 0; i < 8; i++) {
        const OctreeNode* child = node->child(static_cast<size_t>(i));
        if (child != nullptr) {
          // Set bit to 1 for this child
          unsigned char mask = static_cast<unsigned char>(0x01 << (7 - i));
          bits |= mask;

          // Add child to queue
          queue.push(child);
        }
      }

      // Write current node to file
      ofile.write(reinterpret_cast<const char*>(&bits), 1);
      bytesWritten++;
    }

    return bytesWritten;
  }

  /// Read octree from file.
  ///
  /// \param[in] path Path to octree file. Should have file extension .idx
  /// \param[out] octree Octree
  /// \return True on success, false otherwise
  static bool readFromFile(const std::string& fileName, Octree& octree)
  {
    // Open file
    std::ifstream ifile(fileName, std::ios::in | std::ios::binary);
    if (!ifile.is_open()) {
      return false;
    }

    // Read signature
    char signature[17];
    ifile.read(signature, 17);
    if (std::memcmp(signature, "SPATIUMGL_OCTREE\n", 17) != 0) {
      return false;
    }

    // Read extent
    // ...
    // delete octree.root()
    // octree.setBounds()

    // Traverse tree breadth-first with queue
    std::queue<OctreeNode*> queue;
    queue.push(octree.root());
    while (!queue.empty() && !ifile.eof()) {
      // Pop front of queue
      OctreeNode* node = queue.front();
      queue.pop();

      // Read children bits from file
      unsigned char bits;
      ifile.read(reinterpret_cast<char*>(&bits), 1);

      // Iterate bits
      for (unsigned char i = 0; i < 8; i++) {
        unsigned char mask = static_cast<unsigned char>(0x01 << (7 - i));
        bool hasChild = ((bits & mask) > 0 ? true : false);

        if (hasChild) {
          if (node->createChild(static_cast<size_t>(i))) {
            queue.push(node->child(static_cast<size_t>(i)));
          }
          /// \TODO Check for allocation error
        }
      }
    }

    return true;
  }

protected:
  BoundingCube m_bounds;
};

} // namespace idx
} // namespace spgl

#endif // SPATIUMGL_IDX_OCTREE_H

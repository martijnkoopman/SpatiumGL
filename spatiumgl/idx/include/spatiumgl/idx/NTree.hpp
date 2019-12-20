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

#ifndef SPATIUMGL_IDX_NTREE_H
#define SPATIUMGL_IDX_NTREE_H

#include "spatiumgl/Bounds.hpp"
#include "spatiumgl/idx/NTreeNode.hpp"
#include "spatiumglexport.hpp"

namespace spgl {
namespace idx {

template<typename T, size_t N>
struct SPATIUMGL_EXPORT NTreeBounds
  : public BoundsCenter<T, N>
  , public BoundsRadii<T, 1>
{};

template<size_t N>
class SPATIUMGL_EXPORT NTree
{
public:
  /// Constructor.
  ///
  /// \param[in] rootObject Object for root node
  NTree()
    : m_root(new NTreeNode<N>())
  {}

  /// Copy constructor.
  NTree(const NTree& other) = delete;

  /// Move constructor.
  NTree(NTree&& other)
    : m_root(nullptr)
  {
    std::swap(m_root, other.m_root);
  }

  /// Copy assignment operator.
  NTree& operator=(const NTree& other) = delete;

  /// Move assignment operator.
  NTree& operator=(NTree&& other)
  {
    if (this != &other) {
      delete m_root;
      m_root = nullptr;
      std::swap(m_root, other.m_root);
    }
    return *this;
  }

  /// Destructor.
  ~NTree()
  {
    delete m_root;
  }

  /// Get root node.
  ///
  /// \return Root node
  NTreeNode<N>* root() const { return m_root; }

  /// Get iterator pointing to the beginning of the tree (root node).
  ///
  /// This iterator traverses the tree in DEPTH-FIRST order.
  ///
  /// \return Tree iterator
  // NTreeIteratorDF<T, N> beginDF() { return NTreeIteratorDF<T,N>(*this); }

  /// Get iterator pointing to the end of the tree.
  ///
  /// This iterator traverses the tree in DEPTH-FIRST order.
  ///
  /// \return Tree iterator
  // NTreeIteratorDF<T, N> endDF() { return NTreeIteratorDF<T, N>(*this, true);
  // }

  /// Get iterator pointing to the beginning of the tree (root node).
  ///
  /// This iterator traverses the tree in BREADTH-FIRST order.
  ///
  /// \return Tree iterator
  // NTreeIteratorBF<T, N> beginBF() { return NTreeIteratorBF<T, N>(*this); }

  /// Get iterator pointing to the end of the tree.
  ///
  /// This iterator traverses the tree in BREADTH-FIRST order.
  ///
  /// \return Tree iterator
  // NTreeIteratorBF<T, N> endBF() { return NTreeIteratorBF<T, N>(*this, true);
  // }

protected:
  NTreeNode<N>* m_root;
};

using OctreeNode = NTreeNode<8>;
using QuadNode = NTreeNode<4>;
using Quadtree = NTree<4>;

/*
/// \class NTreeIteratorDF
/// \brief Depth-first NTree iterator.
template<size_t N>
class SPATIUMGL_EXPORT NTreeIteratorDF
{
  //...

  /// Get tree node currently being pointed to.
  ///
  /// \return NTreeNode
  const NTreeNode<T, N>* operator*() const { return m_stack.top(); }

protected:
  NTree<T, N>& m_tree;
  bool m_end;
  std::stack<NTreeNode<T, N>> m_stack;
};

/// \class NTreeIteratorBF
/// \brief Breadth-first NTree iterator.
template<typename T, size_t N>
class SPATIUMGL_EXPORT NTreeIteratorBF
{};
*/

} // namespace idx
} // namespace spgl

#endif // SPATIUMGL_IDX_NTREE_H

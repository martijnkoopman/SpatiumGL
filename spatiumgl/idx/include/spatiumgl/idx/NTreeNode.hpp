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

#ifndef SPATIUMGL_IDX_NTREENODE_H
#define SPATIUMGL_IDX_NTREENODE_H

#include "spatiumglexport.hpp"

#include <array> // std::array

namespace spgl {
namespace idx {

/// \class NTreeNode
/// \brief Node in a tree with a fixed number of children.
template<size_t N>
class SPATIUMGL_EXPORT NTreeNode
{
public:
  /// Constructor.
  ///
  /// \param[in] object Object
  NTreeNode()
    : m_children()
  {}

  /// Copy constructor.
  NTreeNode(const NTreeNode& other) = delete;

  /// Move constructor.
  NTreeNode(NTreeNode&& other)
    : m_children()
  {
    m_children.swap(other.m_children);
  }

  /// Copy assignment operator.
  NTreeNode& operator=(const NTreeNode& other) = delete;

  /// Move assignment operator.
  NTreeNode& operator=(NTreeNode&& other)
  {
    if (this != &other) {
      for (size_t i = 0; i < N; i++) {
        delete m_children[i];
        m_children[i] = nullptr;
      }
      m_children.swap(other.m_children);
    }
    return *this;
  }

  /// Destructor.
  ~NTreeNode()
  {
    for (size_t i = 0; i < N; i++) {
      delete m_children[i];
      m_children[i] = nullptr;
    }
  }

  /// Create a child.
  ///
  /// \param[in] index Child index
  /// \param[in] object Object
  /// \return True if created, false if child already exists.
  bool createChild(size_t index)
  {
    if (index >= N) {
      return false;
	}

    if (m_children[index] != nullptr) {
      return false;
    }

    m_children[index] = new NTreeNode<N>;
    return true;
  }

  /// Detele a child and recursively all its children.
  ///
  /// \param[in] index Child index
  /// \return True if deleted, false if child doesn't exist.
  bool deleteChild(size_t index)
  {
    if (index >= N) {
      return false;
    }

    if (m_children[index] == nullptr) {
      return false;
    }

    delete m_children[index];
    m_children[index] = nullptr;

    return true;
  }

  /// Get a child.
  ///
  /// \param[in] index Child index
  /// \return Child or nullptr
  NTreeNode<N>* child(size_t index) const
  {
    if (index >= N) {
      return nullptr;
    }

    /// \todo constexpr check with N
    return m_children[index];
  }

  /// Get child index.
  ///
  /// \param[in] node Child node
  /// \return Index if found, N otherwise.
  size_t childIndex(const NTreeNode<N>* child) const
  {
    if (child == nullptr) {
      return N;
    }

    for (size_t i = 0; i < N; i++) {
      if (m_children[i] == child) {
        return i;
      }
    }

    return N;
  }

protected:
  std::array<NTreeNode<N>*, N> m_children;
};

} // namespace idx
} // namespace spgl

#endif // SPATIUMGL_IDX_NTREENODE_H

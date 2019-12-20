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

#ifndef SPATIUMGL_IOLAS_LASOCTREE_H
#define SPATIUMGL_IOLAS_LASOCTREE_H

#include <spatiumgl/idx/NTree.hpp>

using Point = std::array<double, 3>;
using Extent = std::array<Point, 2>;

class LasOctree : public spgl::idx::NTree<void, 8>
{
  std::array<std::array<double, 3>, 2> computeNodeExtent(
    const spgl::idx::NTree<void, 8>* node) const
  {

  }

protected:
  Extent m_extent;
};

#endif // SPATIUMGL_IOLAS_LASOCTREE_H
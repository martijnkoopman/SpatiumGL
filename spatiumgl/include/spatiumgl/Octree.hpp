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

#ifndef SPATIUMGL_OCTREE_H
#define SPATIUMGL_OCTREE_H

#include "Tree.hpp"
#include "OctreeNode.hpp"
#include "Bounds.hpp"

namespace spatiumgl {

	/// \class Octree
	/// \brief Octree data structure
	///
	/// Octree is a hierarchical data structure composed of nodes (OctreeNodes). 
	/// Each node in the tree can have 8 children. Each child expands one octant of space. 
	/// One node represents the root of the tree.
	class Octree : public Tree<void, 8>
	{
	public:

		/// Constructor
		Octree(const BoundingBox & bounds)
			: Tree<void, 8>(new OctreeNode())
			, m_boundingBox(bounds)
		{
			// Make bounding box cubical
			// ... ?? Really neccasseryy?
		}

		/// Determine index of child (0 - 8) depening on bounding box of parent and positon of a point.
		/// Also outputs the bounding box of this child.
		///
		/// \param[in] boundsParent Bounding box of parent
		/// \param[in] point Point positon (must be within bounding box)
		/// \param[out] boundsChild Bounding box of child
		/// \return Child index (0 = topleft, 1 = topright, 2 = bottom right, 3 = bottom left)
		static size_t determineChild(const BoundingBox & boundsParent, const std::array<double, 3> & point, BoundingBoxT<double, 3> & boundsChild)
		{
			std::array<double, 3> min = boundsParent.min();
			std::array<double, 3> max = boundsParent.max();
			std::array<double, 3> center = boundsParent.center();
			if (point[0] < center[0])
			{
				// Left half
				if (point[1] < center[1])
				{
					// Bottom
					boundsChild = BoundingBox::fromMinMax(min, center);
					return 0;
				}
				else
				{
					// Top
					boundsChild = BoundingBox::fromMinMax({ min[0], center[1] }, { center[0], max[1] });
					return 2;
				}
			}
			else
			{
				// Right half
				if (point[1] < center[1])
				{
					// Top
					boundsChild = BoundingBox::fromMinMax({ center[0], min[1] }, { max[0], center[1] });
					return 1;
				}
				else
				{
					// Bottom
					boundsChild = BoundingBox::fromMinMax(center, max);
					return 3;
				}
			}
		}

		/// Get the bounding box 
		BoundingBox bounds() const
		{
			return m_boundingBox;
		}

		/// Get the maximum point count for a node.
		///
		/// A node is split when it exceeds this number.
		size_t division() const
		{
			return m_division;
		}

	protected:
		const BoundingBox m_boundingBox;
		const size_t m_division;
	};

} // namespace spatiumgl

#endif // SPATIUMGL_OCTREE_H